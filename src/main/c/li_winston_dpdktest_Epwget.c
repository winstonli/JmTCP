#include "li_winston_dpdktest_Epwget.h"

#include <stdio.h>
#include "lepwget.h"

JNIEXPORT void JNICALL Java_li_winston_dpdktest_Epwget_doWget(JNIEnv *jnienv, jclass clazz) {
    char *argv[] = {
        "epwget",
        "216.58.213.142",
        "1"
    };
    main1(3, argv);
}
