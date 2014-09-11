
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>

/*
 * declare Profiler interface here because
 * <google/profiler.h> is C++ header file
 */

int ProfilerStart(u_char* fname);
void ProfilerStop(void);
void ProfilerRegisterThread(void);

static void *ngx_adit_create_conf(ngx_cycle_t *cycle);
static ngx_int_t ngx_adit_worker(ngx_cycle_t *cycle);


typedef struct {
    ngx_str_t  profiles;
} ngx_adit_conf_t;

static ngx_command_t ngx_adit_commands[] = {

    { ngx_string("adit"),
      NGX_MAIN_CONF|NGX_DIRECT_CONF|NGX_CONF_TAKE1,
      ngx_conf_set_str_slot,
      0,
      offsetof(ngx_adit_conf_t, profiles),
      NULL },

    ngx_null_command
};


static ngx_core_module_t  ngx_adit_module_ctx = {
    ngx_string("adit"),
    ngx_adit_create_conf,
    NULL
};


ngx_module_t  ngx_adit_module = {
    NGX_MODULE_V1,
    &ngx_adit_module_ctx,      /* module context */
    ngx_adit_commands,         /* module directives */
    NGX_CORE_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    ngx_adit_worker,           /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static void *
ngx_adit_create_conf(ngx_cycle_t *cycle)
{
    ngx_adit_conf_t  *gptcf;

    gptcf = ngx_pcalloc(cycle->pool, sizeof(ngx_adit_conf_t));
    if (gptcf == NULL) {
        return NULL;
    }

    /*
     * set by ngx_pcalloc()
     *
     *     gptcf->profiles = { 0, NULL };
     */

    return gptcf;
}


static ngx_int_t
ngx_adit_worker(ngx_cycle_t *cycle)
{
    ngx_adit_conf_t  *gptcf;

    gptcf = (ngx_adit_conf_t *)
                ngx_get_conf(cycle->conf_ctx, ngx_adit_module);

    ngx_log_error(NGX_LOG_ERR, cycle->log, ngx_errno, "in adit worker...\n");

    if (gptcf->profiles.len == 0) {
        return NGX_OK;
    }

    ngx_log_error(NGX_LOG_ERR, cycle->log, ngx_errno, "from adit: %s", gptcf->profiles.data);

    return NGX_OK;
}


/* ProfilerStop() is called on Profiler destruction */
