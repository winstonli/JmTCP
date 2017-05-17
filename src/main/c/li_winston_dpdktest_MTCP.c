#include <jni.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <errno.h>
#include <mtcp_api.h>
#include <mtcp_epoll.h>
#include <string.h>

static
void j_mtcp_conf_to_mtcp_conf(JNIEnv *env,
                              jobject j_this,
                              struct mtcp_conf *mtcp_conf);

static
void mtcp_conf_to_j_mtcp_conf(struct mtcp_conf *self,
                              JNIEnv *env,
                              jobject j_mtcp_conf);

static
void j_sockaddr_in_to_sockaddr_in(JNIEnv *env,
                                  jobject j_this,
                                  struct sockaddr_in *sockaddr_in);

static
void sockaddr_in_to_j_sockaddr_in(struct sockaddr_in *sockaddr_in,
                                  JNIEnv *env,
                                  jobject j_sockaddr_in);

void j_mtcp_conf_to_mtcp_conf(JNIEnv *env,
                              jobject j_this,
                              struct mtcp_conf *mtcp_conf) {

    /* Get num_cores field */
    jfieldID num_cores_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "num_cores",
        "I"
    );
    jint j_num_cores = (*env)->GetIntField(env, j_this, num_cores_id);

    mtcp_conf->num_cores = j_num_cores;

    /* Get max_concurrency field */

    jfieldID max_concurrency_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "max_concurrency",
        "I"
    );
    jint j_max_concurrency = (*env)->GetIntField(env, j_this, max_concurrency_id);

    mtcp_conf->max_concurrency = j_max_concurrency;

    /* Get max_num_buffers field */

    jfieldID max_num_buffers_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "max_num_buffers",
        "I"
    );
    jint j_max_num_buffers = (*env)->GetIntField(env, j_this, max_num_buffers_id);

    mtcp_conf->max_num_buffers = j_max_num_buffers;

    /* Get rcvbuf_size field */

    jfieldID rcvbuf_size_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "rcvbuf_size",
        "I"
    );
    jint j_rcvbuf_size = (*env)->GetIntField(env, j_this, rcvbuf_size_id);

    mtcp_conf->rcvbuf_size = j_rcvbuf_size;

    /* Get sndbuf_size field */

    jfieldID sndbuf_size_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "sndbuf_size",
        "I"
    );
    jint j_sndbuf_size = (*env)->GetIntField(env, j_this, sndbuf_size_id);

    mtcp_conf->sndbuf_size = j_sndbuf_size;

    /* Get tcp_timewait field */

    jfieldID tcp_timewait_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "tcp_timewait",
        "I"
    );
    jint j_tcp_timewait = (*env)->GetIntField(env, j_this, tcp_timewait_id);

    mtcp_conf->tcp_timewait = j_tcp_timewait;

    /* Get tcp_timeout field */

    jfieldID tcp_timeout_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "tcp_timeout",
        "I"
    );
    jint j_tcp_timeout = (*env)->GetIntField(env, j_this, tcp_timeout_id);

    mtcp_conf->tcp_timeout = j_tcp_timeout;

}

void mtcp_conf_to_j_mtcp_conf(struct mtcp_conf *self,
                              JNIEnv *env,
                              jobject j_mtcp_conf) {

    /* Set num_cores field */
    jfieldID num_cores_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "num_cores",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, num_cores_id, self->num_cores);

    /* Set max_concurrency field */
    jfieldID max_concurrency_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "max_concurrency",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, max_concurrency_id, self->max_concurrency);

    /* Set max_num_buffers field */
    jfieldID max_num_buffers_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "max_num_buffers",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, max_num_buffers_id, self->max_num_buffers);

    /* Set rcvbuf_size field */
    jfieldID rcvbuf_size_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "rcvbuf_size",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, rcvbuf_size_id, self->rcvbuf_size);

    /* Set sndbuf_size field */
    jfieldID sndbuf_size_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "sndbuf_size",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, sndbuf_size_id, self->sndbuf_size);

    /* Set tcp_timewait field */
    jfieldID tcp_timewait_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "tcp_timewait",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, tcp_timewait_id, self->tcp_timewait);

    /* Set tcp_timeout field */
    jfieldID tcp_timeout_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_mtcp_conf),
        "tcp_timeout",
        "I"
    );
    (*env)->SetIntField(env, j_mtcp_conf, tcp_timeout_id, self->tcp_timeout);

}

void j_sockaddr_in_to_sockaddr_in(JNIEnv *env,
                                  jobject j_this,
                                  struct sockaddr_in *sockaddr_in) {

    /* Get sin_family field */
    jfieldID sin_family_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "sin_family",
        "S"
    );
    jshort j_sin_family = (*env)->GetShortField(env, j_this, sin_family_id);
    sockaddr_in->sin_family = j_sin_family;

    /* Get sin_addr field */
    jfieldID sin_addr_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "sin_addr",
        "Ljava/lang/String;"
    );
    jstring j_sin_addr = (*env)->GetObjectField(env, j_this, sin_addr_id);
    const char *sin_addr = (*env)->GetStringUTFChars(env, j_sin_addr, 0);
    if (strncmp("0.0.0.0", sin_addr, 8) == 0) {
        sockaddr_in->sin_addr.s_addr = INADDR_ANY;
    } else {
        sockaddr_in->sin_addr.s_addr = inet_addr(sin_addr);
    }
    (*env)->ReleaseStringUTFChars(env, j_sin_addr, sin_addr);

    /* Get port field */

    jfieldID port_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_this),
        "port",
        "I"
    );
    jint j_port = (*env)->GetIntField(env, j_this, port_id);
    sockaddr_in->sin_port = htons(j_port);

}

void sockaddr_in_to_j_sockaddr_in(struct sockaddr_in *sockaddr_in,
                                  JNIEnv *env,
                                  jobject j_sockaddr_in) {

    /* Set sin_family field */
    jfieldID sin_family_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_sockaddr_in),
        "sin_family",
        "S"
    );
    (*env)->SetShortField(
        env,
        j_sockaddr_in,
        sin_family_id,
        sockaddr_in->sin_family
    );

    /* Set sin_addr field */
    jfieldID sin_addr_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_sockaddr_in),
        "sin_addr",
        "Ljava/lang/String;"
    );

    char *sin_addr = inet_ntoa(sockaddr_in->sin_addr);
    jstring j_sin_addr = (*env)->NewStringUTF(env, sin_addr);
    (*env)->SetObjectField(env, j_sockaddr_in, sin_addr_id, j_sin_addr);

    /* Set port field */

    jfieldID port_id = (*env)->GetFieldID(
        env,
        (*env)->GetObjectClass(env, j_sockaddr_in),
        "port",
        "I"
    );
    (*env)->SetIntField(
        env,
        j_sockaddr_in,
        port_id,
        ntohs(sockaddr_in->sin_port)
    );

}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_init
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1init(JNIEnv *env,
                                                      jclass clazz,
                                                      jstring j_config_file) {
    const char *config_file = (*env)->GetStringUTFChars(env, j_config_file, 0);
    int ret = mtcp_init((char *) config_file);
    (*env)->ReleaseStringUTFChars(env, j_config_file, config_file);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_destroy
 * Signature: ()V
 */
JNIEXPORT
void JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1destroy(JNIEnv *env,
                                                         jclass clazz) {
    mtcp_destroy();
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_getconf
 * Signature: (Lli/winston/dpdktest/MtcpConf;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1getconf(JNIEnv *env,
                                                         jclass clazz,
                                                         jobject j_conf) {
    struct mtcp_conf mtcp_conf;
    int ret = mtcp_getconf(&mtcp_conf);
    mtcp_conf_to_j_mtcp_conf(&mtcp_conf, env, j_conf);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_setconf
 * Signature: (Lli/winston/dpdktest/MtcpConf;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1setconf(JNIEnv *env,
                                                         jclass clazz,
                                                         jobject j_conf) {
    struct mtcp_conf mtcp_conf;
    j_mtcp_conf_to_mtcp_conf(env, j_conf, &mtcp_conf);
    return mtcp_setconf(&mtcp_conf);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_core_affinitize
 * Signature: (I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1core_1affinitize(JNIEnv *env,
                                                                  jclass clazz,
                                                                  jint j_cpu) {
    return mtcp_core_affinitize(j_cpu);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_create_context
 * Signature: (I)Lli/winston/dpdktest/MtcpContext;
 */
JNIEXPORT
jlong
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1create_1context(JNIEnv *env,
                                                            jclass clazz,
                                                            jint j_cpu) {
    return (jlong) mtcp_create_context(j_cpu);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_destroy_context
 * Signature: (Lli/winston/dpdktest/MtcpContext;)V
 */
JNIEXPORT
void
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1destroy_1context(JNIEnv *env,
                                                             jclass clazz,
                                                             jlong j_mctx) {
    mtcp_destroy_context((mctx_t) j_mctx);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_register_signal
 * Signature: (ILli/winston/dpdktest/MtcpSighandler;)Lli/winston/dpdktest/MtcpSighandler;
 */
JNIEXPORT
jobject
JNICALL
Java_li_winston_dpdktest_MTCP_mtcp_1register_1signal(JNIEnv *env,
                                                     jclass clazz,
                                                     jint j_signum,
                                                     jobject j_handler) {
    fprintf(stderr, "mtcp_register_signal unimplemented\n");
    return NULL;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_pipe
 * Signature: (Lli/winston/dpdktest/MtcpContext;[I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1pipe(JNIEnv *env,
                                                      jclass clazz,
                                                      jlong j_mctx,
                                                      jintArray j_pipeid) {
    int *p_pipeid = (*env)->GetIntArrayElements(env, j_pipeid, 0);
    int pipeid[] = {
        p_pipeid[0],
        p_pipeid[1]
    };
    int ret = mtcp_pipe((mctx_t) j_mctx, pipeid);
    (*env)->ReleaseIntArrayElements(env, j_pipeid, p_pipeid, 0);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_getsockopt
 * Signature: (Lli/winston/dpdktest/MtcpContext;III[I)I
 */
JNIEXPORT
jint
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1getsockopt(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid,
                                                       jint j_level,
                                                       jint j_optname,
                                                       jintArray j_optval) {
    int *p_optval = (*env)->GetIntArrayElements(env, j_optval, 0);
    socklen_t optlen = 1;
    int ret = mtcp_getsockopt(
        (mctx_t) j_mctx,
        j_sockid,
        j_level,
        j_optname,
        p_optval,
        &optlen
    );
    (*env)->ReleaseIntArrayElements(env, j_optval, p_optval, 0);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_setsockopt
 * Signature: (Lli/winston/dpdktest/MtcpConf;III[I)I
 */
JNIEXPORT
jint
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1setsockopt(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid,
                                                       jint j_level,
                                                       jint j_optname,
                                                       jintArray j_optval) {
    int *p_optval = (*env)->GetIntArrayElements(env, j_optval, 0);
    int ret = mtcp_setsockopt(
        (mctx_t) j_mctx,
        j_sockid,
        j_level,
        j_optname,
        p_optval,
        1
    );
    (*env)->ReleaseIntArrayElements(env, j_optval, p_optval, JNI_ABORT);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_setsock_nonblock
 * Signature: (Lli/winston/dpdktest/MtcpContext;I)I
 */
JNIEXPORT
jint
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1setsock_1nonblock(JNIEnv *env,
                                                              jclass clazz,
                                                              jlong j_mctx,
                                                              jint j_sockid) {
    return mtcp_setsock_nonblock((mctx_t) j_mctx, j_sockid);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_socket_ioctl
 * Signature: (Lli/winston/dpdktest/MtcpContext;II[I)I
 */
JNIEXPORT
jint
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1socket_1ioctl(JNIEnv *env,
                                                          jclass clazz,
                                                          jlong j_mctx,
                                                          jint j_sockid,
                                                          jint j_request,
                                                          jintArray j_argp) {
    int *p_argp = (*env)->GetIntArrayElements(env, j_argp, 0);
    int ret = mtcp_socket_ioctl((mctx_t) j_mctx, j_sockid, j_request, p_argp);
    (*env)->ReleaseIntArrayElements(env, j_argp, p_argp, 0);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_socket
 * Signature: (Lli/winston/dpdktest/MtcpContext;III)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1socket(JNIEnv *jenv,
                                                        jclass clazz,
                                                        jlong j_mctx,
                                                        jint j_domain,
                                                        jint j_type,
                                                        jint j_protocol) {
    return mtcp_socket((mctx_t) j_mctx, j_domain, j_type, j_protocol);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_bind
 * Signature: (Lli/winston/dpdktest/MtcpContext;ILli/winston/dpdktest/SockaddrIn;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1bind(JNIEnv *env,
                                                      jclass clazz,
                                                      jlong j_mctx,
                                                      jint j_sockid,
                                                      jobject j_addr) {
    struct sockaddr_in addr;
    j_sockaddr_in_to_sockaddr_in(env, j_addr, &addr);
    return mtcp_bind(
        (mctx_t) j_mctx,
        j_sockid,
        (const struct sockaddr *) &addr,
        sizeof(struct sockaddr_in)
    );
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_listen
 * Signature: (Lli/winston/dpdktest/MtcpContext;II)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1listen(JNIEnv *env,
                                                        jclass clazz,
                                                        jlong j_mctx,
                                                        jint j_sockid,
                                                        jint j_backlog) {
    return mtcp_listen((mctx_t) j_mctx, j_sockid, j_backlog);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_accept
 * Signature: (Lli/winston/dpdktest/MtcpContext;ILli/winston/dpdktest/SockaddrIn;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1accept(JNIEnv *env,
                                                        jclass clazz,
                                                        jlong j_mctx,
                                                        jint j_sockid,
                                                        jobject j_addr) {
    struct sockaddr_in addr;
    socklen_t addrlen;
    int ret = mtcp_accept(
        (mctx_t) j_mctx,
        j_sockid,
        (struct sockaddr *) &addr,
        &addrlen
    );
    sockaddr_in_to_j_sockaddr_in(&addr, env, j_addr);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_init_rss
 * Signature: (Lli/winston/dpdktest/MtcpContext;Ljava/lang/String;ILjava/lang/String;I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1init_1rss(JNIEnv *env,
                                                           jclass clazz,
                                                           jlong j_mctx,
                                                           jstring j_saddr_base,
                                                           jint j_num_addr,
                                                           jstring j_daddr,
                                                           jint j_dport) {
    const char *saddr = (*env)->GetStringUTFChars(env, j_saddr_base, 0);
    const char *daddr = (*env)->GetStringUTFChars(env, j_daddr, 0);
    int ret = mtcp_init_rss(
        (mctx_t) j_mctx,
        inet_addr(saddr),
        j_num_addr,
        inet_addr(daddr),
        htons(j_dport)
    );
    (*env)->ReleaseStringUTFChars(env, j_saddr_base, saddr);
    (*env)->ReleaseStringUTFChars(env, j_daddr, daddr);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_connect
 * Signature: (Lli/winston/dpdktest/MtcpContext;ILli/winston/dpdktest/SockaddrIn;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1connect(JNIEnv *env,
                                                         jclass clazz,
                                                         jlong j_mctx,
                                                         jint j_sockid,
                                                         jobject j_addr) {
    struct sockaddr_in addr;
    j_sockaddr_in_to_sockaddr_in(env, j_addr, &addr);
    return mtcp_connect(
        (mctx_t) j_mctx,
        j_sockid,
        (struct sockaddr *) &addr,
        sizeof(struct sockaddr_in)
    );
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_close
 * Signature: (Lli/winston/dpdktest/MtcpContext;I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1close(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid) {
    return mtcp_close((mctx_t) j_mctx, j_sockid);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_abort
 * Signature: (Lli/winston/dpdktest/MtcpContext;I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1abort(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid) {
    return mtcp_abort((mctx_t) j_mctx, j_sockid);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_read
 * Signature: (Lli/winston/dpdktest/MtcpContext;I[B)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1read(JNIEnv *env,
                                                      jclass clazz,
                                                      jlong j_mctx,
                                                      jint j_sockid,
                                                      jbyteArray j_buf) {
    jbyte *buf = (*env)->GetByteArrayElements(env, j_buf, NULL);
    jint len = (*env)->GetArrayLength(env, j_buf);
    int ret = mtcp_read((mctx_t) j_mctx, j_sockid, buf, len);
    (*env)->ReleaseByteArrayElements(env, j_buf, buf, 0);
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_readv
 * Signature: (Lli/winston/dpdktest/MtcpContext;I[[B)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1readv(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid,
                                                       jobjectArray j_iov) {
    int j_iov_len = (*env)->GetArrayLength(env, j_iov);
    struct iovec iov[j_iov_len];
    jbyteArray j_iov_arrs[j_iov_len];
    jbyte *j_iov_bufs[j_iov_len];
    for (int i = 0; i < j_iov_len; ++i) {
        jbyteArray j_iov_arr = (*env)->GetObjectArrayElement(env, j_iov, i);
        jbyte *j_iov_buf = (*env)->GetByteArrayElements(env, j_iov_arr, NULL);
        iov[i].iov_base = j_iov_buf;
        iov[i].iov_len = (*env)->GetArrayLength(env, j_iov_arr);
        j_iov_bufs[i] = j_iov_buf;
        j_iov_arrs[i] = j_iov_arr;
    }
    int ret = mtcp_readv(
        (mctx_t) j_mctx,
        j_sockid,
        &iov[0],
        j_iov_len
    );
    for (int i = 0; i < j_iov_len; ++i) {
        (*env)->ReleaseByteArrayElements(env, j_iov_arrs[i], j_iov_bufs[i], 0);
    }
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_write
 * Signature: (Lli/winston/dpdktest/MtcpContext;I[B)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1write(JNIEnv *env,
                                                       jclass clazz,
                                                       jlong j_mctx,
                                                       jint j_sockid,
                                                       jobject j_buf) {
    char *buf = (*env)->GetDirectBufferAddress(env, j_buf);
    jlong len = (*env)->GetDirectBufferCapacity(env, j_buf);
    return mtcp_write((mctx_t) j_mctx, j_sockid, buf, len);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_writev
 * Signature: (Lli/winston/dpdktest/MtcpContext;I[[B)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1writev(JNIEnv *env,
                                                        jclass clazz,
                                                        jlong j_mctx,
                                                        jint j_sockid,
                                                        jobjectArray j_iov) {
    int j_iov_len = (*env)->GetArrayLength(env, j_iov);
    struct iovec iov[j_iov_len];
    jbyteArray j_iov_arrs[j_iov_len];
    jbyte *j_iov_bufs[j_iov_len];
    for (int i = 0; i < j_iov_len; ++i) {
        jbyteArray j_iov_arr = (*env)->GetObjectArrayElement(env, j_iov, i);
        jbyte *j_iov_buf = (*env)->GetByteArrayElements(env, j_iov_arr, NULL);
        iov[i].iov_base = j_iov_buf;
        iov[i].iov_len = (*env)->GetArrayLength(env, j_iov_arr);
        j_iov_bufs[i] = j_iov_buf;
        j_iov_arrs[i] = j_iov_arr;
    }
    int ret = mtcp_writev(
        (mctx_t) j_mctx,
        j_sockid,
        &iov[0],
        j_iov_len
    );
    for (int i = 0; i < j_iov_len; ++i) {
        (*env)->ReleaseByteArrayElements(env, j_iov_arrs[i], j_iov_bufs[i], 0);
    }
    return ret;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_epoll_create
 * Signature: (Lli/winston/dpdktest/MtcpContext;I)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1epoll_1create(JNIEnv *env,
                                                               jclass clazz,
                                                               jlong j_mctx,
                                                               jint j_size) {
    return mtcp_epoll_create((mctx_t) j_mctx, j_size);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_epoll_ctl
 * Signature: (Lli/winston/dpdktest/MtcpContext;IIILli/winston/dpdktest/MtcpEpollEvent;)I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1epoll_1ctl(JNIEnv *env,
                                                            jclass clazz,
                                                            jlong j_mctx,
                                                            jint j_epid,
                                                            jint j_op,
                                                            jint j_sockid,
                                                            jint j_event,
                                                            jlong j_data) {
    struct mtcp_epoll_event event = {
        .events = j_event,
        .data = {
            .u64 = j_data
        }
    };
    return mtcp_epoll_ctl((mctx_t) j_mctx, j_epid, j_op, j_sockid, &event);
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    mtcp_epoll_wait
 * Signature: (Lli/winston/dpdktest/MtcpContext;I[Lli/winston/dpdktest/MtcpEpollEvent;II)I
 */
JNIEXPORT
jint
JNICALL Java_li_winston_dpdktest_MTCP_mtcp_1epoll_1wait(JNIEnv *env,
                                                        jclass clazz,
                                                        jlong j_mctx,
                                                        jint j_epid,
                                                        jobject j_events,
                                                        jint j_timeout) {
    struct mtcp_epoll_event *events = (*env)->GetDirectBufferAddress(
        env,
        j_events
    );
    jlong maxevents = (*env)->GetDirectBufferCapacity(
        env,
        j_events
    ) / sizeof(struct mtcp_epoll_event);

    return mtcp_epoll_wait(
        (mctx_t) j_mctx,
        j_epid,
        events,
        maxevents,
        j_timeout
    );
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    errno
 * Signature: ()I
 */
JNIEXPORT
jint JNICALL Java_li_winston_dpdktest_MTCP_errno(JNIEnv *env, jclass clazz) {
    return errno;
}

/*
 * Class:     li_winston_dpdktest_MTCP
 * Method:    set_errno
 * Signature: (I)V
 */
JNIEXPORT
void JNICALL Java_li_winston_dpdktest_MTCP_set_1errno(JNIEnv *env,
                                                      jclass clazz,
                                                      jint j_errno) {
    errno = j_errno;
}
