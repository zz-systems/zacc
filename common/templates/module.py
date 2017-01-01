import yasha
from enum import Enum


class OpType(Enum):
    NONE = "none",
    UNARY = "unary",
    BINARY = "binary",
    CUSTOM = "custom"


def postprocess(config):
    clean_config = {}

    print("---------------------------------------------------")

    for (module, module_config) in config.items():
        clean_config[module] = {}

        for (operator, operator_config) in module_config.items():
            op_args = ""
            op_type = OpType.BINARY
            op_instr = ""
            op_prefix = bool(1);
            op_modifier = "";

            if type(operator_config) is str:  # assume default-binary operator
                op_instr = operator_config
            else:  # fetch type and instruction
                if "type" in operator_config:
                    op_type = OpType[operator_config["type"].upper()]

                if "args" in operator_config:
                    op_args = operator_config["args"]

                if "prefix" in operator_config:
                    op_prefix = operator_config["prefix"] == "true"

                if "modifier" in operator_config:
                    op_modifier = operator_config["modifier"].rstrip() + " "

                op_instr = operator_config["instruction"]

            clean_config[module][operator] = [];

            name = module + "_" + operator if op_prefix else operator
            args = process_args(op_type, op_args)
            instructions = dict(process_instructions(op_type, op_instr))

            for (branch, branch_ret_type) in process_branch(op_instr):
                clean_config[module][operator].append({
                    "rettype": op_modifier + branch_ret_type,
                    "conditional": len(instructions) > 1,
                    "name": name,
                    "args": args,
                    "instruction": instructions[branch]
                })

            print(op_instr)
            print("===================================================")
            print(instructions)  # clean_config[module][operator])
            print("---------------------------------------------------")
    return {"config": clean_config}


def process_branch(op_instr):
    if type(op_instr) is dict:

        assert ("default" in op_instr)

        dispatch_if = "dispatcher::has_{0}"
        dispatch_if_not = "!dispatcher::has_{0}"
        rettype = "std::enable_if_t<{0}, composed_t>"

        special = [(k, v) for (k, v) in op_instr.items() if k != "default"];

        for (branch, instruction) in special:
            condition = " && ".join(
                [dispatch_if.format(branch)] + [dispatch_if_not.format(b) for (b, i) in special if b != branch])
            yield branch, rettype.format(condition)

        condition = " && ".join([dispatch_if_not.format(b) for (b, i) in special])
        yield "default", rettype.format(condition)
    else:
        yield "default", "composed_t"


def process_args(op_type, op_args):
    # if already set: passthrough
    if op_args:
        if type(op_args) == list:
            return "const composed_t " + ", const composed_t ".join(op_args);
        else:
            return args;

    if op_type == OpType.UNARY:
        return "const composed_t one"
    if op_type == OpType.BINARY:
        return "const composed_t one, const composed_t other"


def process_instructions(op_type, op_instr):
    # assume simple operations
    if type(op_instr) is str:
        if op_instr.find('(') == -1:  # simple method name without args.
            if op_type == OpType.UNARY:
                op_instr += "(one.get_value())"
            elif op_type == OpType.BINARY:
                op_instr += "(one.get_value(), other.get_value())"

        if op_instr.find('return ') == -1:
            op_instr = "return " + op_instr

        if op_instr.rfind(';') == -1:
            op_instr += ';'

        yield "default", [op_instr.rstrip()]

    elif type(op_instr) is list:
        yield "default", op_instr
    elif type(op_instr) is dict:
        for (branch, instruction) in op_instr.items():
            yield branch, [dict(process_instructions(op_type, instruction))["default"][0]]
    else:
        raise "Wrong instruction"


class YamlParser(yasha.YamlParser):
    def parse(self, file):
        variables = yasha.YamlParser.parse(self, file)
        return postprocess(variables)
