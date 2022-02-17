package cn.huolala.testcapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import cn.huolala.mylibrary.Arithmetic
import java.io.File

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Arithmetic.init()
        setContentView(R.layout.activity_main)
        val textView = findViewById<TextView>(R.id.show_native_content)

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

        findViewById<Button>(R.id.test_page).setOnClickListener {
            val intent = Intent(this, TestPageActivity::class.java)
            startActivity(intent)
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