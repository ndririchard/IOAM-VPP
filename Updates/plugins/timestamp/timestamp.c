/*
 * Copyright (c) 2020 TNO.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @file
 * @brief Timestamp Plugin, plugin API / trace / CLI handling.
 */

#include <vnet/vnet.h>
#include <vnet/plugin/plugin.h>
#include <timestamp/timestamp.h>

#include <vlibapi/api.h>
#include <vlibmemory/api.h>

#include <timestamp/timestamp.api_enum.h>
#include <timestamp/timestamp.api_types.h>

#define REPLY_MSG_ID_BASE sm->msg_id_base
#include <vlibapi/api_helper_macros.h>

/* *INDENT-OFF* */
VLIB_PLUGIN_REGISTER () = {
    .version = TIMESTAMP_PLUGIN_BUILD_VER,
    .description = "Timestamp plugin for VPP",
};
/* *INDENT-ON* */

timestamp_main_t timestamp_main;

/**
 * @brief Enable/disable the timestamp plugin. 
 *
 * Action function shared between message handler and debug CLI.
 */

int timestamp_enable_disable (timestamp_main_t * sm, u32 sw_if_index,
                              int enable_disable)
{
  vnet_sw_interface_t * sw;
  int rv = 0;

  /* Utterly wrong? */
  if (pool_is_free_index (sm->vnet_main->interface_main.sw_interfaces, sw_if_index))
  {
    return VNET_API_ERROR_INVALID_SW_IF_INDEX;
  }

  /* Not a physical port? */
  sw = vnet_get_sw_interface (sm->vnet_main, sw_if_index);
  if (sw->type != VNET_SW_INTERFACE_TYPE_HARDWARE)
  {
    return VNET_API_ERROR_INVALID_SW_IF_INDEX;
  }
  
  vnet_feature_enable_disable ("device-input", "timestamp-ingress", sw_if_index, enable_disable, 0, 0);
  vnet_feature_enable_disable ("interface-output", "timestamp-egress", sw_if_index, enable_disable, 0, 0);

  return rv;
}

static clib_error_t *
timestamp_enable_disable_command_fn (vlib_main_t * vm,
                                     unformat_input_t * input,
                                     vlib_cli_command_t * cmd)
{
  timestamp_main_t * sm = &timestamp_main;
  u32 sw_if_index = ~0;
  int enable_disable = 1;
    
  int rv;

  while (unformat_check_input (input) != UNFORMAT_END_OF_INPUT) 
  {
    if (unformat (input, "disable")) enable_disable = 0;
    else if (unformat (input, "%U", unformat_vnet_sw_interface, sm->vnet_main, &sw_if_index));
    else break;
  }

  if (sw_if_index == ~0)
  {
    return clib_error_return (0, "Please specify an interface...");
  }
    
  rv = timestamp_enable_disable (sm, sw_if_index, enable_disable);

  switch(rv) 
  {
    case 0:
      break;

    case VNET_API_ERROR_INVALID_SW_IF_INDEX:
      return clib_error_return(0, "Invalid interface, only works on physical ports");
      break;

    case VNET_API_ERROR_UNIMPLEMENTED:
      return clib_error_return (0, "Device driver doesn't support");
      break;

    default:
      return clib_error_return (0, "timestamp_enable_disable returned %d", rv);
  }
  return 0;
}

/**
 * @brief CLI command to enable/disable the timestamp plugin.
 */
VLIB_CLI_COMMAND (enable_disable_timestamp, static) = {
    .path = "timestamp",
    .short_help = 
    "timestamp <interface-name> [disable]",
    .function = timestamp_enable_disable_command_fn,
};

/**
 * @brief Plugin API message handler.
 */
static void vl_api_timestamp_enable_disable_t_handler
(vl_api_timestamp_enable_disable_t * mp)
{
  vl_api_timestamp_enable_disable_reply_t * rmp;
  timestamp_main_t * sm = &timestamp_main;
  int rv;

  rv = timestamp_enable_disable (sm, ntohl(mp->sw_if_index), (int) (mp->enable_disable));
  
  REPLY_MACRO(VL_API_TIMESTAMP_ENABLE_DISABLE_REPLY);
}

/* API definitions */
#include <timestamp/timestamp.api.c>

/**
 * @brief Initialize the timestamp plugin.
 */
static clib_error_t * timestamp_init (vlib_main_t * vm)
{
  timestamp_main_t * sm = &timestamp_main;

  sm->vnet_main =  vnet_get_main ();
  /* Add our API messages to the global name_crc hash table */
  sm->msg_id_base = setup_message_id_table ();

  return 0;
}

VLIB_INIT_FUNCTION (timestamp_init) =
{
  .runs_after = VLIB_INITS("ip_neighbor_init"),
};
/**
 * @brief Hook the timestamp plugin into the VPP graph hierarchy.
 */
VNET_FEATURE_INIT (timestamp_ingress, static) = 
{
  .arc_name = "device-input",
  .node_name = "timestamp-ingress",
  .runs_before = VNET_FEATURES ("ethernet-input"),
};
VNET_FEATURE_INIT (timestamp_egress, static) = 
{
  .arc_name = "interface-output",
  .node_name = "timestamp-egress",
  .runs_before = VNET_FEATURES ("interface-tx"),
};
