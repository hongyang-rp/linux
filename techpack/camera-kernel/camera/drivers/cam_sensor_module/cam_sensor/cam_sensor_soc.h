/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2024, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _CAM_SENSOR_SOC_H_
#define _CAM_SENSOR_SOC_H_

#include "cam_sensor_dev.h"

/**
 * @s_ctrl: Sensor ctrl structure
 *
 * Parses sensor dt
 */
int cam_sensor_parse_dt(struct cam_sensor_ctrl_t *s_ctrl);

/**
 * @s_ctrl: Sensor ctrl structure
 *
 * Release power domain
 */
void cam_sensor_release_power_domain(struct cam_sensor_ctrl_t *s_ctrl);
#endif /* _CAM_SENSOR_SOC_H_ */
