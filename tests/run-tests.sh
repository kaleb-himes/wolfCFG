#!/bin/sh

# get c Pre Processor Macros for all four dirs, both source dirs, and both
# header dirs while accounting for duplicates across all four
#---- Uncomment to run #

#./run m wolfssl/src wolfssl/wolfcrypt/src wolfssl/wolfssl wolfssl/wolfssl/wolfcrypt > wolfssl-pp-all.txt

#----#



# do the same as above but ignore duplicates across directories
#---- Uncomment to run #

#./run e wolfssl/src > wolfssl-pp.txt
#./run e wolfssl/wolfcrypt/src >> wolfssl-pp.txt
#./run e wolfssl/wolfssl >> wolfssl-pp.txt
#./run e wolfssl/wolfssl/wolfcrypt >> wolfssl-pp.txt

#----#


# run the benchmarks for all configure options found in ./configure -h output
# with the exception of those in the ignore_opts array found in the header
# "<wolfCFG-root>/include/configurator_common.h"
#---- Uncomment to run #

#./run b

#----#


# create a custom build that only includes a subset of wolfSSL functionality
#
# current custom supported builds are:
# aes_only
#
#---- Uncomment to run #

runDefaultTest(){
    printf '%s\n' "Test ${1} ${2}"
    echo 'n' | ./run c ${1} ${2} > /dev/null
    RESULT=$?
    printf '%s\n' "RESULT: $RESULT"
    ./${1}/run
    RESULT=$?
    printf '%s\n' "RESULT: $RESULT"
}

runArmTest(){
    printf '%s\n' "Test ${1} ${2}"
    echo 'n' | ./run c ${1} ${2}
    RESULT=$?
    printf '%s\n' "RESULT: $RESULT"
}

runArmTest "rsa_pss_pkcs" "ARM-THUMB=/usr/local/gcc_arm/gcc-arm-none-eabi-7-2017-q4/bin/arm-none-eabi-"
#runDefaultTest aes_only DEFAULT
#runDefaultTest rsa_pss_pkcs DEFAULT
#runDefaultTest rsa_pss_pkcs_sv_ned DEFAULT
#runDefaultTest sha256_ecc DEFAULT
#runDefaultTest sha512_only DEFAULT
#runDefaultTest ecc_only DEFAULT

#./run m pp_testing_dir NULL NULL NULL 1 1

#----#
