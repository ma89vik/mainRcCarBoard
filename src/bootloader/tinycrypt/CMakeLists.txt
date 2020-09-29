
set(SRCS "tinycrypt/lib/source/sha256.c"
        "tinycrypt/lib/source/ecc.c"
        "tinycrypt/lib/source/ecc_dh.c"
        "tinycrypt/lib/source/ecc_dsa.c"
        "tinycrypt/lib/source/utils.c")

add_library(tinycrypt STATIC ${SRCS})
target_include_directories(tinycrypt PUBLIC "tinycrypt/lib/include")