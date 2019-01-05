/**
 * @file ptp4l.c
 * @brief PTP Boundary Clock main program
 * @note Copyright (C) 2011 Richard Cochran <richardcochran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "clock.h"
#include "config.h"
#include "ntpshm.h"
#include "pi.h"
#include "print.h"
#include "raw.h"
#include "sk.h"
#include "transport.h"
#include "udp6.h"
#include "uds.h"
#include "util.h"
#include "version.h"

int assume_two_step = 0;

static void usage(char *progname)
{
	fprintf(stderr,
		"\nusage: %s [options]\n\n"
		" Delay Mechanism\n\n"
		" -A        Auto, starting with E2E\n"
		" -E        E2E, delay request-response (default)\n"
		" -P        P2P, peer delay mechanism\n\n"
		" Network Transport\n\n"
		" -2        IEEE 802.3\n"
		" -4        UDP IPV4 (default)\n"
		" -6        UDP IPV6\n\n"
		" Time Stamping\n\n"
		" -H        HARDWARE (default)\n"
		" -S        SOFTWARE\n"
		" -L        LEGACY HW\n\n"
		" Other Options\n\n"
		" -f [file] read configuration from 'file'\n"
		" -i [dev]  interface device to use, for example 'eth0'\n"
		"           (may be specified multiple times)\n"
		" -p [dev]  PTP hardware clock device to use, default auto\n"
		"           (ignored for SOFTWARE/LEGACY HW time stamping)\n"
		" -s        slave only mode (overrides configuration file)\n"
		" -l [num]  set the logging level to 'num'\n"
		" -m        print messages to stdout\n"
		" -q        do not print messages to the syslog\n"
		" -v        prints the software version and exits\n"
		" -h        prints this message and exits\n"
		"\n",
		progname);
}

int main(int argc, char *argv[])
{
	char *config = NULL, *req_phc = NULL, *progname;
	int c, err = -1, index, print_level;
	struct clock *clock = NULL;
	struct option *opts;
	struct config *cfg;
#ifdef KSZ_1588_PTP
	char *config_save = NULL;
	char dev_names[20];
	int mports = 0;
	int two_step = 0;
	int vlan = 0;
#endif

	if (handle_term_signals())
		return -1;

	cfg = config_create();
	if (!cfg) {
		return -1;
	}
	opts = config_long_options(cfg);

	/* Process the command line arguments. */
	progname = strrchr(argv[0], '/');
	progname = progname ? 1+progname : argv[0];
#ifdef KSZ_1588_PTP
	while (EOF != (c = getopt_long(argc, argv, "ABEPN246HSLRZf:i:p:sl:mn:o:qvh",
#else
	while (EOF != (c = getopt_long(argc, argv, "AEP246HSLf:i:p:sl:mqvh",
#endif
				       opts, &index))) {
		switch (c) {
		case 0:
			if (config_parse_option(cfg, opts[index].name, optarg))
				goto out;
			break;
		case 'A':
			if (config_set_int(cfg, "delay_mechanism", DM_AUTO))
				goto out;
			break;
		case 'E':
			if (config_set_int(cfg, "delay_mechanism", DM_E2E))
				goto out;
			break;
		case 'P':
			if (config_set_int(cfg, "delay_mechanism", DM_P2P))
				goto out;
			break;
#ifdef KSZ_1588_PTP
		case 'B':
			config_set_int(cfg, "transparent", 0);
			break;
		case 'N':
			if (config_set_int(cfg, "delay_mechanism", DM_NONE))
				goto out;
			break;
#endif
		case '2':
			if (config_set_int(cfg, "network_transport",
					    TRANS_IEEE_802_3))
				goto out;
			break;
		case '4':
			if (config_set_int(cfg, "network_transport",
					    TRANS_UDP_IPV4))
				goto out;
			break;
		case '6':
			if (config_set_int(cfg, "network_transport",
					    TRANS_UDP_IPV6))
				goto out;
			break;
		case 'H':
			if (config_set_int(cfg, "time_stamping", TS_HARDWARE))
				goto out;
			break;
		case 'S':
			if (config_set_int(cfg, "time_stamping", TS_SOFTWARE))
				goto out;
			break;
		case 'L':
			if (config_set_int(cfg, "time_stamping", TS_LEGACY_HW))
				goto out;
			break;
#ifdef KSZ_1588_PTP
		case 'R':
			if (config_set_int(cfg, "c37_238", 1))
				goto out;
			vlan = 1;
			break;
		case 'Z':
			if (config_set_int(cfg, "twoStepFlag", 1))
				goto out;
			two_step = 1;
			break;
		case 'n':
			mports = atoi(optarg);
			break;
#endif
		case 'f':
#ifdef KSZ_1588_PTP
			if (config) {
				config_save = optarg;
				break;
			}
#endif
			config = optarg;
			break;
		case 'i':
#ifdef KSZ_1588_PTP
			if (0 == cfg->n_interfaces)
				strncpy(dev_names, optarg, 20);
#endif
			if (!config_create_interface(optarg, cfg))
				goto out;
			break;
		case 'p':
			req_phc = optarg;
			break;
		case 's':
			if (config_set_int(cfg, "slaveOnly", 1)) {
				goto out;
			}
			break;
		case 'l':
			if (get_arg_val_i(c, optarg, &print_level,
					  PRINT_LEVEL_MIN, PRINT_LEVEL_MAX))
				goto out;
			config_set_int(cfg, "logging_level", print_level);
			break;
		case 'm':
			config_set_int(cfg, "verbose", 1);
			break;
		case 'q':
			config_set_int(cfg, "use_syslog", 0);
			break;
		case 'v':
			version_show(stdout);
			return 0;
		case 'h':
			usage(progname);
			return 0;
		case '?':
			usage(progname);
			goto out;
		default:
			usage(progname);
			goto out;
		}
	}

#ifdef KSZ_1588_PTP
	if (mports > cfg->n_interfaces && cfg->n_interfaces == 1) {
		int i;
		int lan;
		int len;
		char port_names[20];
		char *dot;
		char *dot2;

		len = strlen(dev_names);
		strcpy(port_names, dev_names);
		dot = strchr(port_names, '.');
		if (dot) {
			dot++;

			/* This is the VLAN extension. */
			dot2 = strchr(dot, '.');
			lan = atoi(dot);
			*dot = '\0';
		} else if (!vlan) {
			lan = dev_names[len - 1] - '0';
			port_names[len - 1] = '\0';
		} else {
			fprintf(stderr, "VLAN configuration not right\n");
			goto out;
		}
		for (i = cfg->n_interfaces; i < mports; i++) {
			if (dot2)
				sprintf(dev_names, "%s%u%s", port_names,
					lan + i, dot2);
			else
				sprintf(dev_names, "%s%u", port_names,
					lan + i);
			if (!config_create_interface(dev_names, cfg))
				break;
		}

		/* Create one final device for master clock operation. */
		if (dot && config_get_int(cfg, NULL, "transparent")) {
			dot--;
			*dot = '\0';
			if (dot2)
				sprintf(dev_names, "%s%s", port_names, dot2);
			else
				sprintf(dev_names, "%s", port_names);
			config_create_interface(dev_names, cfg);
		}
	}

	/* Do not automatically create interface from configuration file. */
	if (cfg->n_interfaces >= 1)
		cfg->no_auto_create = 1;
#endif

	if (config && (c = config_read(config, cfg))) {
		return c;
	}
#ifdef KSZ_1588_PTP
	if (!config) {
		/* Default clock is one-step. */
		if (!two_step && config_set_int(cfg, "twoStepFlag", 0))
			goto out;
	} else if (config_save)
		c = config_read(config_save, cfg);
#endif

	print_set_progname(progname);
	print_set_tag(config_get_string(cfg, NULL, "message_tag"));
	print_set_verbose(config_get_int(cfg, NULL, "verbose"));
	print_set_syslog(config_get_int(cfg, NULL, "use_syslog"));
	print_set_level(config_get_int(cfg, NULL, "logging_level"));

	assume_two_step = config_get_int(cfg, NULL, "assume_two_step");
	sk_check_fupsync = config_get_int(cfg, NULL, "check_fup_sync");
	sk_tx_timeout = config_get_int(cfg, NULL, "tx_timestamp_timeout");

	if (config_get_int(cfg, NULL, "clock_servo") == CLOCK_SERVO_NTPSHM) {
		config_set_int(cfg, "kernel_leap", 0);
		config_set_int(cfg, "sanity_freq_limit", 0);
	}

	if (STAILQ_EMPTY(&cfg->interfaces)) {
		fprintf(stderr, "no interface specified\n");
		usage(progname);
		goto out;
	}

	clock = clock_create(cfg->n_interfaces > 1 ? CLOCK_TYPE_BOUNDARY :
			     CLOCK_TYPE_ORDINARY, cfg, req_phc);
	if (!clock) {
		fprintf(stderr, "failed to create a clock\n");
		goto out;
	}

	err = 0;

	while (is_running()) {
		if (clock_poll(clock))
			break;
	}
#ifdef KSZ_1588_PTP
	if (config_save && cfg->changed)
		c = config_write(config_save, cfg);
#endif
out:
	if (clock)
		clock_destroy(clock);
	config_destroy(cfg);
	return err;
}
