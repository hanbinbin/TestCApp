package cn.huolala.testcapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import cn.huolala.mylibrary.Arithmetic
import java.io.File

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Arithmetic.init()
        setContentView(R.layout.activity_main)
        val textView = findViewById<TextView>(R.id.show_native_content)
        textView.text = "getStringFromJNI: ${Arithmetic.getStringFromJNI()}  \n" +
                " getPointerValueFormJNI: ${Arithmetic.getPointerValueFormJNI()} \n" +
                " getTestNullPointer: ${Arithmetic.getTestNullPointer()} \n" +
                " getTestPointerAndArray: ${Arithmetic.getTestPointerAndArray()} \n" +
                " getTestPointerToPointer: ${Arithmetic.getTestPointerToPointer()} \n" +
                " getTestPointerToFunction: ${Arithmetic.getTestPointerToFunction()} \n" +
                " getTestFunctionReturnPointer: ${Arithmetic.getTestFunctionReturnPointer()} \n" +
                " getTestReference: ${Arithmetic.getTestReference()} \n" +
                " getTestReferenceParam: ${Arithmetic.getTestReferenceParam()} \n" +
                " getTestFunctionReturnReference: ${Arithmetic.getTestFunctionReturnReference()} \n" +
                " getTestDateAndTime: ${Arithmetic.getTestDateAndTime()} \n" +
                " getTestStruct: ${Arithmetic.getTestStruct()} \n" +
                " getTestTypeDef: ${Arithmetic.getTestTypeDef()} \n" +
                " getTestDefineClassObject: ${Arithmetic.getTestDefineClassObject()} \n" +
                " getTestPolymorphism: ${Arithmetic.getTestPolymorphism()} \n" +
                " getTestPackage: ${Arithmetic.getTestPackage()} \n" +
                " getTestInterface: ${Arithmetic.getTestInterface()} \n" +
                " getWriteContentToFile: ${Arithmetic.getWriteContentToFile()} \n" +
                " getCharAndString: ${Arithmetic.getCharAndString()} \n" +
                " getPlaceHolder: ${Arithmetic.getPlaceHolder()} \n" +
                " getTestException: ${Arithmetic.getTestException()} \n" +
                " getTestDynamicRAM: ${Arithmetic.getTestDynamicRAM()} \n" +
                " getTestNameSpace: ${Arithmetic.getTestNameSpace()} \n" +
                " getTestTemplate: ${Arithmetic.getTestTemplate()} \n" +
                " getTestDefine: ${Arithmetic.getTestDefine()}"
        //设置内容，让c++去处理
        findViewById<TextView>(R.id.set_native_content).setOnClickListener {
            Arithmetic.setData(101, 101)
            var a: Long = 0
            //native 计算1亿次所使用的的时间
            val start: Long = System.currentTimeMillis()
            for (i in 0..100000000) {
                a++
            }
            val end: Long = System.currentTimeMillis()
            Log.e("kotlin costTime", "消耗时间(ms)：" + (end - start))

            //c++ 计算一亿次所用时间
            val start1: Long = System.currentTimeMillis()
            Arithmetic.getTestTraverse()
            val end1: Long = System.currentTimeMillis()
            Log.e("c++ costTime", "消耗时间(ms)：" + (end1 - start1))

            Arithmetic.getTestJavaTraverse()
        }
        //获取刚刚c++处理的内容
        findViewById<TextView>(R.id.get_native_content).setOnClickListener {
            textView.text = "处理结果为：${Arithmetic.getData()}"
            Log.e("123", "${Arithmetic.getTestContent()}")
        }

        createDir()
    }

    private fun createDir() {
        Log.e("MainActivity", externalCacheDir?.path ?: "")
        val file = File(externalCacheDir?.path, "test.txt")
        if (file.isFile) {
            return
        }
        file.createNewFile()
    }
}