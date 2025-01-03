/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2023, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#ifndef _ARM_SMMU_QCOM_H
#define _ARM_SMMU_QCOM_H

struct qcom_smmu {
	struct arm_smmu_device smmu;
	const struct qcom_smmu_match_data *data;
	bool bypass_quirk;
	u8 bypass_cbndx;
	u32 stall_enabled;
	struct mutex tbu_list_lock;  /* protects tbu_list */
	struct list_head tbu_list;
};

enum qcom_smmu_impl_reg_offset {
	QCOM_SMMU_TBU_PWR_STATUS,
	QCOM_SMMU_STATS_SYNC_INV_TBU_ACK,
	QCOM_SMMU_MMU2QSS_AND_SAFE_WAIT_CNTR,
};

struct qcom_smmu_config {
	const u32 *reg_offset;
};

struct qcom_smmu_match_data {
	const struct actlr_config *actlrcfg;
	size_t actlrcfg_size;
	const struct actlr_config *actlrcfg_gfx;
	size_t actlrcfg_gfx_size;
	const struct qcom_smmu_config *cfg;
	const struct arm_smmu_impl *impl;
	const struct arm_smmu_impl *adreno_impl;
};

irqreturn_t qcom_smmu_context_fault(int irq, void *dev);

#ifdef CONFIG_ARM_SMMU_QCOM_DEBUG
void qcom_smmu_tlb_sync_debug(struct arm_smmu_device *smmu);
#else
static inline void qcom_smmu_tlb_sync_debug(struct arm_smmu_device *smmu) { }
#endif

#endif /* _ARM_SMMU_QCOM_H */
