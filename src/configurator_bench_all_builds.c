#include <configurator_common.h>

void cfg_bench_all_configs(void)
{
    char c_pwd[LONGEST_PATH];
    char c_cmd[LONGEST_COMMAND];
    char* configOutFname = "config-out.txt";
    int ret;
    int default_baseline = 0;
    int difference;
    char allConfigSingles[MOST_CONFIGS][LONGEST_CONFIG];
    int i, j;

    cfg_clear_cmd(c_pwd);
    cfg_clear_cmd(c_cmd);

    cfg_clone_target_repo("wolfssl/wolfssl");

    /* get path to working directory */
    if (getcwd(c_pwd, LONGEST_PATH) == NULL)
        cfg_abort();

    /* cd to wolfssl root dir and run autogen.sh */
    printf("Getting the library ready for testing...\n");
    cfg_build_cd_cmd(c_cmd, c_pwd);
    cfg_build_cmd(c_cmd, "/wolfssl", " && ./autogen.sh", NULL, NULL);
    system(c_cmd);
    cfg_clear_cmd(c_cmd);

    cfg_build_cd_cmd(c_cmd, c_pwd);
    system(c_cmd);
    cfg_clear_cmd(c_cmd);

    /* get a baseline for comparison */
    printf("Configuring for baseline comparison...\n");
    default_baseline = cfg_run_config_opts(c_pwd, DEFAULT_CONFIG);

    /* run configure to output the help menu */
    /* echo the result to file */
    cfg_clear_cmd(c_cmd);
    cfg_build_cd_cmd(c_cmd, c_pwd);
    cfg_build_cmd(c_cmd, "/wolfssl && ./configure -h > ../",
              configOutFname, NULL, NULL);
    system(c_cmd);
    cfg_clear_cmd(c_cmd);

    /* scrub the file for configure options */
    /* store configure options in a char[][] */
    for (i = 0; i < MOST_CONFIGS; i++) {
        XMEMSET(allConfigSingles[i], 0, LONGEST_CONFIG);
    }

    cfg_scrub_config_out(configOutFname, allConfigSingles);
    /* read out the options one at a time and compare to baseline */
    for (i = 0; i < MOST_CONFIGS; i++) {
        if (XSTRNCMP(allConfigSingles[i], "LAST_LINE", 9) == 0) {
            printf("aborting at %d\n", i);
            break;
        }
        /* TODO: if default on don't run */
        cfg_check_increase(default_baseline, allConfigSingles[i]);
        /* TODO: if default off don't run */
        cfg_check_decrease(default_baseline, allConfigSingles[i]);
    }

}

