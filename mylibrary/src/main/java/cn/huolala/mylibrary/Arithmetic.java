package cn.huolala.mylibrary;

import android.util.Log;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Author by binbinhan,
 * Email binbin.han@huolala.cn,
 * Date on 12/18/21.
 * PS: Not easy to write code, please indicate.
 */
public final class Arithmetic {
    private static final AtomicBoolean sInitialized = new AtomicBoolean();

    public static void init() {
        if (sInitialized.get()) {
            return;
        }
        System.loadLibrary("native-lib");
        sInitialized.set(true);
    }

    public static void setData(int a, int b) {
        jniSetData(a, b);
    }

    public static int getData() {
        return jniGetData();
    }

    public static int getTestContent() {
        return jniGetTestContent();
    }

    public static String getStringFromJNI() {
        return stringFromJNI();
    }

    public static String getPointerValueFormJNI() {
        return getPointerValue();
    }

    public static String getTestNullPointer() {
        return testNullPointer();
    }

    public static String getTestPointerAndArray() {
        return testPointerAndArray();
    }

    public static String getTestPointerToPointer() {
        return testPointerToPointer();
    }

    public static String getTestPointerToFunction() {
        return testPointerToFunction();
    }

    public static String getTestFunctionReturnPointer() {
        return testFunctionReturnPointer();
    }

    public static String getTestReference() {
        return testReference();
    }

    public static String getTestReferenceParam() {
        return testReferenceParam();
    }

    public static String getTestFunctionReturnReference() {
        return testFunctionReturnReference();
    }

    public static String getTestDateAndTime() {
        return testDateAndTime();
    }

    public static String getTestStruct() {
        return testStruct();
    }

    public static String getTestTypeDef() {
        return testTypeDef();
    }

    public static String getTestDefineClassObject() {
        return testDefineClassObject();
    }

    public static String getTestPolymorphism() {
        return testPolymorphism();
    }

    public static String getTestPackage() {
        return testPackage();
    }

    public static String getTestInterface() {
        return testInterface();
    }

    public static String getWriteContentToFile() {
        return writeContentToFile();
    }

    public static String getCharAndString() {
        return charAndString();
    }

    public static String getPlaceHolder() {
        return placeHolder();
    }

    public static String getTestException() {
        return testException();
    }

    public static String getTestDynamicRAM() {
        return testDynamicRAM();
    }

    public static String getTestNameSpace() {
        return testNameSpace();
    }

    public static String getTestTemplate() {
        return testTemplate();
    }

    public static void getTestJavaTraverse() {
        int a_a = 0;
        //c++ 计算一亿次所用时间
        long start = System.currentTimeMillis();
        for (int ind = 0; ind < 100000000; ind++) {
            a_a++;
        }
        long end = System.currentTimeMillis();
        Log.e("java costTime", "消耗时间(ms)：" + (end - start));
    }

    public static void getTestTraverse() {
        testTraverse();
    }

    private static native void jniSetData(int a, int b);

    private static native int jniGetData();

    private static native int jniGetTestContent();

    private static native String stringFromJNI();

    private static native String getPointerValue();

    private static native String testNullPointer();

    private static native String testPointerAndArray();

    private static native String testPointerToPointer();

    private static native String testPointerToFunction();

    private static native String testFunctionReturnPointer();

    private static native String testReference();

    private static native String testReferenceParam();

    private static native String testFunctionReturnReference();

    private static native String testDateAndTime();

    private static native void testTraverse();

    private static native String testStruct();

    private static native String testTypeDef();

    private static native String testDefineClassObject();

    private static native String testPolymorphism();

    private static native String testPackage();

    private static native String testInterface();

    private static native String writeContentToFile();

    private static native String charAndString();

    private static native String placeHolder();

    private static native String testException();

    private static native String testDynamicRAM();

    private static native String testNameSpace();

    private static native String testTemplate();
}
