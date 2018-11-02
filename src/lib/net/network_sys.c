/* Copyright (c) 2018, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file network_sys.c
 * \brief Subsystem object for networking setup.
 **/

#include "orconfig.h"
#include "lib/subsys/subsys.h"
#include "lib/net/network_sys.h"
#include "lib/net/resolve.h"
#include "lib/net/socket.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

static int
init_network_sys(void)
{
  if (network_init() < 0)
    return -1;

  return 0;
}

static void
shutdown_network_sys(void)
{
#ifdef _WIN32
  WSACleanup();
#endif
  tor_free_getaddrinfo_cache();
}

const subsys_fns_t sys_network = {
  .name = "network",
  .level = -90,
  .supported = true,
  .initialize = init_network_sys,
  .shutdown = shutdown_network_sys,
};
