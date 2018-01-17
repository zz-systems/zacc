from enum import Enum, auto

class Tokens(Enum):
    TYPE    = auto()
    TARGET  = auto()
    VECTOR  = auto()
    MASK    = auto()
    SCALAR  = auto()
    SIZE    = auto()
    ALIGN   = auto()

    TRAITS  = auto()
    DEFAULT = auto()
    BOOLEAN = auto()
    UNSIGNED= auto()
    SHARED  = auto()

    MODULES = auto()

    ARGS    = auto()
    INIT    = auto()
    RAW     = auto()
    FROM    = auto()
    TO      = auto()

    PREFIX  = auto()
    SUFFIX  = auto()
    RETURNS = auto()
    REQUIRES= auto()
    BODY    = auto()
    MANGLING= auto()


class Lexer:
    def __init__(self, mapping):
        self._mapping = mapping
        self._inv_mapping = {v: k for k, v in mapping.items()}

    def lex(self, data):
        if isinstance(data, dict):
            return { self._mapping.get(k, k): self.lex(v) for k,v in data.items()}
        else:
            return data

    def unlex(self, data):
        if isinstance(data, dict):
            return { self._inv_mapping.get(k, k): self.unlex(v) for k,v in data.items()}
        else:
            return self._inv_mapping.get(data, data)


class LexerV1(Lexer):
    def __init__(self):
        mapping = {
            "type"      : Tokens.TYPE,
            "branch"    : Tokens.TARGET,
            "vector_t"  : Tokens.VECTOR,
            "mask_t"    : Tokens.MASK,
            "scalar_t"  : Tokens.SCALAR,
            "vec_size"  : Tokens.SIZE,
            "alignment" : Tokens.ALIGN,

            "traits"    : Tokens.TRAITS,
            "default"   : Tokens.DEFAULT,
            "boolean"   : Tokens.BOOLEAN,
            "unsigned"  : Tokens.UNSIGNED,
            "shared"    : Tokens.SHARED,

            "modules"   : Tokens.MODULES,

            "args"      : Tokens.ARGS,
            "init"      : Tokens.INIT,
            "raw"       : Tokens.RAW,
            "from"      : Tokens.FROM,
            "to"        : Tokens.TO,

            "prefix"    : Tokens.PREFIX,
            "suffix"    : Tokens.SUFFIX,
            "returns"   : Tokens.RETURNS,
            "requires"  : Tokens.REQUIRES,
            "body"      : Tokens.BODY,

            "mangling"  : Tokens.MANGLING
        }

        super().__init__(mapping)