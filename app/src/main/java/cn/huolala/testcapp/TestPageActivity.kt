package cn.huolala.testcapp

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import cn.huolala.mylibrary.Arithmetic

/**
 * Author by binbinhan,
 * Email binbin.han@huolala.cn,
 * Date on 2/17/22.
 * PS: Not easy to write code, please indicate.
 */
class TestPageActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.test_page_activity)

        findViewById<Button>(R.id.getStringFromJNI).setOnClickListener {
            Arithmetic.getStringFromJNI()
        }

        findViewById<Button>(R.id.getPointerValueFormJNI).setOnClickListener {
            Arithmetic.getPointerValueFormJNI()
        }

        findViewById<Button>(R.id.getTestNullPointer).setOnClickListener {
            Arithmetic.getTestNullPointer()
        }

        findViewById<Button>(R.id.getTestPointerAndArray).setOnClickListener {
            Arithmetic.getTestPointerAndArray()
        }

        findViewById<Button>(R.id.getTestPointerToPointer).setOnClickListener {
            Arithmetic.getTestPointerToPointer()
        }

        findViewById<Button>(R.id.getTestPointerToFunction).setOnClickListener {
            Arithmetic.getTestPointerToFunction()
        }

        findViewById<Button>(R.id.getTestFunctionReturnPointer).setOnClickListener {
            Arithmetic.getTestFunctionReturnPointer()
        }

        findViewById<Button>(R.id.getTestReference).setOnClickListener {
            Arithmetic.getTestReference()
        }

        findViewById<Button>(R.id.getTestReferenceParam).setOnClickListener {
            Arithmetic.getTestReferenceParam()
        }

        findViewById<Button>(R.id.getTestFunctionReturnReference).setOnClickListener {
            Arithmetic.getTestFunctionReturnReference()
        }

        findViewById<Button>(R.id.getTestDateAndTime).setOnClickListener {
            Arithmetic.getTestDateAndTime()
        }

        findViewById<Button>(R.id.getTestStruct).setOnClickListener {
            Arithmetic.getTestStruct()
        }

        findViewById<Button>(R.id.getTestTypeDef).setOnClickListener {
            Arithmetic.getTestTypeDef()
        }

        findViewById<Button>(R.id.getTestDefineClassObject).setOnClickListener {
            Arithmetic.getTestDefineClassObject()
        }

        findViewById<Button>(R.id.getTestPolymorphism).setOnClickListener {
            Arithmetic.getTestPolymorphism()
        }

        findViewById<Button>(R.id.getTestPackage).setOnClickListener {
            Arithmetic.getTestPackage()
        }

        findViewById<Button>(R.id.getTestInterface).setOnClickListener {
            Arithmetic.getTestInterface()
        }

        findViewById<Button>(R.id.getWriteContentToFile).setOnClickListener {
            Arithmetic.getWriteContentToFile()
        }

        findViewById<Button>(R.id.getCharAndString).setOnClickListener {
            Arithmetic.getCharAndString()
        }

        findViewById<Button>(R.id.getPlaceHolder).setOnClickListener {
            Arithmetic.getPlaceHolder()
        }

        findViewById<Button>(R.id.getTestException).setOnClickListener {
            Arithmetic.getTestException()
        }

        findViewById<Button>(R.id.getTestDynamicRAM).setOnClickListener {
            Arithmetic.getTestDynamicRAM()
        }

        findViewById<Button>(R.id.getTestNameSpace).setOnClickListener {
            Arithmetic.getTestNameSpace()
        }

        findViewById<Button>(R.id.getTestTemplate).setOnClickListener {
            Arithmetic.getTestTemplate()
        }

        findViewById<Button>(R.id.getTestDefine).setOnClickListener {
            Arithmetic.getTestDefine()
        }

        findViewById<Button>(R.id.getTestSignal).setOnClickListener {
            Arithmetic.getTestSignal()
        }

        findViewById<Button>(R.id.getTestMutiThread).setOnClickListener {
            Arithmetic.getTestMutiThread()
        }
    }
}