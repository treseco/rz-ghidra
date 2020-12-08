// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef RZ_GHIDRA_SLEIGHANALVALUE_H
#define RZ_GHIDRA_SLEIGHANALVALUE_H

#include "SleighAsm.h"

struct SleighAnalValue: public RzAnalysisValue
{
public:
	SleighAnalValue()
	{
		access = RzAnalysisValueAccess(0);
		absolute = memref = base = delta = imm = mul = 0;
		seg = reg = regdelta = nullptr;
	}

	static SleighAnalValue resolve_arg(RzAnalysis *analysis, const PcodeOperand *arg);

	static std::vector<SleighAnalValue> resolve_out(RzAnalysis *analysis,
                                           std::vector<Pcodeop>::const_iterator curr_op,
                                           std::vector<Pcodeop>::const_iterator end_op,
                                           const PcodeOperand *arg);

	bool is_valid() const { return absolute != -1; }
	bool is_imm() const { return type == RZ_ANALYSIS_VAL_IMM; }
	bool is_reg() const { return type == RZ_ANALYSIS_VAL_REG; }
	bool is_mem() const { return type == RZ_ANALYSIS_VAL_MEM; }

	void invalid() { absolute = -1; }
	void mem(uint4 size);
	RzAnalysisValue *dup() const;

private:
	static RzAnalysisValueType type_from_values(const SleighAnalValue &in0, const SleighAnalValue &in1);

	template<typename T>
	static inline T inner_max(T foo, T bar)
	{
		return foo > bar? foo: bar;
	}
};

#endif // RZ_GHIDRA_SLEIGHANALVALUE_H