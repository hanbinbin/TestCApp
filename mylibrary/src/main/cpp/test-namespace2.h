//
// Created by binbinHan on 2/16/22.
//

#ifndef TESTCAPP_TEST_NAMESPACE2_H
#define TESTCAPP_TEST_NAMESPACE2_H

namespace TestNameSpace {
    void play(int a);

    //int num; 因为 test-namespace1.h 中已经声明有同名的变量，取消注释会造成重定义错误
}

#endif //TESTCAPP_TEST_NAMESPACE2_H
