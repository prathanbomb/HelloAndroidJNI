/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package th.co.digio

import android.app.Activity
import android.os.Bundle
import android.widget.TextView

class HelloJni : Activity() {
    /** Called when the activity is first created.  */
    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        val tv = TextView(this)
        try {
            checkLicense()
        } catch (e: Exception) {
            e.printStackTrace()
        }
        tv.text = stringFromJNI()
        setContentView(tv)
    }

    val stringFromJava: String
        get() = "String from Java"

    /* A native method that is implemented by the
     * 'hello-jni' native library, which is packaged
     * with this application.
     */
    external fun stringFromJNI(): String?

    @Throws(Exception::class)
    external fun checkLicense()

    companion object {
        /* this is used to load the 'hello-jni' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.hellojni/lib/libhello-jni.so at
     * installation time by the package manager.
     */
        init {
            System.loadLibrary("license-jni")
        }
    }
}