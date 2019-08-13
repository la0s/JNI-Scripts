//http://mydevspace.blogspot.com/2015/05/android-ndkjni-aes.html
jbyteArray aesencrypt128bit(JNIEnv* env, int appversion, int bitnumber, jbyteArray data){
    // 자바에서 암호화 함수를 불러와서 암호화를 진행
    LOGD("NDK : %d / %d", appversion, bitnumber);

    // SecretKeySpec skeySpec = new SecretKeySpec(key.getBytes("UTF-8"), "AES");    
    jclass cls_SecretKeySpe = (*env)->FindClass(env, "javax/crypto/spec/SecretKeySpec");
    jmethodID constructor_SecretKeySpe = (*env)->GetMethodID(env, cls_SecretKeySpe, "<init>", "([BLjava/lang/String;)V");
    jobject myKey = NULL;

    if(bitnumber == 128){
        myKey = (*env)->NewObject(env, cls_SecretKeySpe, constructor_SecretKeySpe, getKey(env, appversion), (*env)->NewStringUTF(env, "AES"));
    }
    else if(bitnumber == 256){
        myKey = (*env)->NewObject(env, cls_SecretKeySpe, constructor_SecretKeySpe, getKey256(env, appversion), (*env)->NewStringUTF(env, "AES"));
    }

    // IvParameterSpec ivspec = new IvParameterSpec(key.substring(0,16).getBytes("UTF-8"))    
    jclass cls_IvParameterSpec = (*env)->FindClass(env, "javax/crypto/spec/IvParameterSpec");
    jmethodID constructor_IvParameterSpec = (*env)->GetMethodID(env, cls_IvParameterSpec, "<init>", "([B)V");
    jobject ivspec = NULL;

    if(bitnumber == 128){
        ivspec = (*env)->NewObject(env, cls_IvParameterSpec, constructor_IvParameterSpec, getIvKey(env, appversion));
    }
    else if(bitnumber == 256){
        ivspec = (*env)->NewObject(env, cls_IvParameterSpec, constructor_IvParameterSpec, getIvKey256(env, appversion));
    }

    // Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");    
    jclass cls_Cipher = (*env)->FindClass(env, "javax/crypto/Cipher");
    jmethodID mid_getInstance = (*env)->GetStaticMethodID(env, cls_Cipher, "getInstance", "(Ljava/lang/String;)Ljavax/crypto/Cipher;");
    jobject obj_Cipher = (*env)->CallStaticObjectMethod(env, cls_Cipher, mid_getInstance, (*env)->NewStringUTF(env, "AES/CBC/PKCS5Padding"));

    // cipher.init(Cipher.DECRYPT_MODE, skeySpec, ivspec); 
    jfieldID fid = (*env)->GetStaticFieldID(env, cls_Cipher, "ENCRYPT_MODE", "I");
    jint cipher_mode = (*env)->GetStaticIntField(env, cls_Cipher, fid);

    jclass cls_Cipher_init = (*env)->GetObjectClass(env, obj_Cipher);
    jmethodID mid_init = (*env)->GetMethodID(env, cls_Cipher_init, "init", "(ILjava/security/Key;Ljava/security/spec/AlgorithmParameterSpec;)V");
    (*env)->CallVoidMethod(env, obj_Cipher, mid_init, cipher_mode, myKey, ivspec);

    // encrypted = cipher.doFinal(bytes);    
    jmethodID mid_doFinal = (*env)->GetMethodID(env, cls_Cipher_init, "doFinal", "([B)[B");
    jbyteArray encrypted_data = (jbyteArray)(*env)->CallObjectMethod(env, obj_Cipher, mid_doFinal, data);

    (*env)->DeleteLocalRef(env, cls_Cipher);          //Release Cipher    
    (*env)->DeleteLocalRef(env, myKey);
    (*env)->DeleteLocalRef(env, cls_SecretKeySpe);    //Release SecretKeySpec    
    (*env)->DeleteLocalRef(env, ivspec);
    (*env)->DeleteLocalRef(env, cls_IvParameterSpec); //Release IvParameterSpec    
    (*env)->DeleteLocalRef(env, obj_Cipher);
    (*env)->DeleteLocalRef(env, cls_Cipher_init);

    return encrypted_data;
}