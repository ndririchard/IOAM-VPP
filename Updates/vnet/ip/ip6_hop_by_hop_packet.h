/*
 * Copyright (c) 2015 Cisco and/or its affiliates.
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
#ifndef __included_ip6_hop_by_hop_packet_h__
#define __included_ip6_hop_by_hop_packet_h__

// This is directly from the IPv6 hop-by-hop extension header
typedef struct
{
  /* Protocol for next header */
  u8 protocol;
  /*
   * Length of hop_by_hop header in 8 octet units,
   * not including the first 8 octets
   */
  u8 length;
  u8 padding[2];
} ip6_hop_by_hop_header_t;

// This is what goes in the "Option Data & Padding" of the IPv6 hop-by-hop extension header
typedef struct
{
  /* Option Type */
#define HBH_OPTION_TYPE_SKIP_UNKNOWN (0x00)
#define HBH_OPTION_TYPE_DISCARD_UNKNOWN (0x40)
#define HBH_OPTION_TYPE_DISCARD_UNKNOWN_ICMP (0x80)
#define HBH_OPTION_TYPE_DISCARD_UNKNOWN_ICMP_NOT_MCAST (0xc0)
#define HBH_OPTION_TYPE_HIGH_ORDER_BITS (0xc0)
#define HBH_OPTION_TYPE_DATA_CHANGE_ENROUTE (1<<5)
  u8 type;
  /* Length in octets of the option data field */
  u8 length;
  u8 reserved;
  /* Prealloc, incremental, pot, e2e */
  u8 ioam_type;
} ip6_hop_by_hop_option_t;

/* $$$$ IANA banana constants */
#define HBH_OPTION_TYPE_IOAM_TRACE_DATA_LIST 49	/* Third highest bit set (change en-route) */
#define HBH_OPTION_TYPE_IOAM_PROOF_OF_TRANSIT 50	/* Third highest bit set (change en-route) */
#define HBH_OPTION_TYPE_IOAM_EDGE_TO_EDGE 17

#endif /* __included_ip6_hop_by_hop_packet_h__ */

/*
 * fd.io coding-style-patch-verification: ON
 *
 * Local Variables:
 * eval: (c-set-style "gnu")
 * End:
 */
