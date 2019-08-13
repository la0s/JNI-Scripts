//0x1检测“/dev/socket/qemud”，“/dev/qemu_pipe”这两个通道
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkPipes(JNIEnv* env,jclass thiz){
	jstring jstr1 = (*env)->NewStringUTF(env,"/dev/socket/qemud");
	jstring jstr2 = (*env)->NewStringUTF(env,"/dev/qemu_pipe");
	jclass jc_file = (*env)->FindClass(env,"java/io/File");
	jmethodID jm_FILE = (*env)->GetMethodID(env,jc_file,"<init>","(Ljava/lang/String;)V");
	jobject jo_file_str1 = (*env)->NewObject(env,jc_file,jm_FILE,jstr1);
	jobject jo_file_str2 = (*env)->NewObject(env,jc_file,jm_FILE,jstr2);
	jmethodID jm_exists = (*env)->GetMethodID(env,jc_file,"exists","()Z");
	jboolean jb_file1_exists = (*env)->CallBooleanMethod(env,jo_file_str1,jm_exists);
	jboolean jb_file2_exists = (*env)->CallBooleanMethod(env,jo_file_str2,jm_exists);
	if(jb_file1_exists == JNI_TRUE){
		LOGV("Find/dev/socket/qemud!");
	}
	if(jb_file2_exists == JNI_TRUE){
		LOGV("Find/dev/qemu_pipe!");
	}
	if(jb_file1_exists == JNI_TRUE || jb_file2_exists == JNI_TRUE){
		return (*env)->NewStringUTF(env,"FindEmulator!");
	} 
	else{
		return (*env)->NewStringUTF(env,"NotFindEmulator!");
	}
}
//0×2检测驱动文件内容，读取文件内容，然后检查已知QEmu的驱动程序的列表（未完成）
//0×3检测模拟器上特有的几个文件
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkEmulatorFiles(JNIEnv* env,jclass thiz){
	jstring jstr_so = (*env)->NewStringUTF(env,"/system/lib/libc_malloc_debug_qemu.so");
	jstring jstr_trace = (*env)->NewStringUTF(env,"/sys/qemu_trace");
	jstring jstr_props = (*env)->NewStringUTF(env,"/system/bin/qemu-props");
	jclassj c_file = (*env)->FindClass(env,"java/io/File");
	jmethodID jm_FILE = (*env)->GetMethodID(env,jc_file,"<init>","(Ljava/lang/String;)V");
	jobject jo_file_so = (*env)->NewObject(env,jc_file,jm_FILE,jstr_so);
	jobject jo_file_trace = (*env)->NewObject(env,jc_file,jm_FILE,jstr_trace);
	jobject jo_file_props = (*env)->NewObject(env,jc_file,jm_FILE,jstr_props);
	jmethodID jm_exists = (*env)->GetMethodID(env,jc_file,"exists","()Z");
	jBoolean jb_file_so = (*env)->CallBooleanMethod(env,jo_file_so,jm_exists);
	jBoolean jb_file_trace = (*env)->CallBooleanMethod(env,jo_file_trace,jm_exists);
	jBoolean jb_file_props = (*env)->CallBooleanMethod(env,jo_file_props,jm_exists);
	if(jb_file_so == JNI_TRUE){
		LOGV("Find/system/lib/libc_malloc_debug_qemu.so!");
	}
	if(jb_file_trace == JNI_TRUE){
		LOGV("Find/sys/qemu_trace!");
	}
	if(jb_file_props == JNI_TRUE){
		LOGV("Find/system/bin/qemu-props!");
	}
	if(jb_file_so == JNI_TRUE||jb_file_trace == JNI_TRUE||jb_file_props == JNI_TRUE){
		return (*env)->NewStringUTF(env,"FindEmulatorBycheckFiles!");
	} 
	else{
		return (*env)->NewStringUTF(env,"NotFindEmulatorBycheckFiles!");
	}
}
//0×4检测模拟器默认的电话号码
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkPhoneNumber(JNIEnv*env,jclassthiz,jobjectmContext){
	jclass jc_context = (*env)->FindClass(env,"android/content/Context");
	jmethodID jm_getSystemService = (*env)->GetMethodID(env,jc_context,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID jf_TELEPHONY_SERVICE = (*env)->GetStaticFieldID(env,jc_context,"TELEPHONY_SERVICE","Ljava/lang/String;");
	jobject jo_telephonyService = (*env)->GetStaticObjectField(env,jc_context,jf_TELEPHONY_SERVICE);
	jobject jo_telephonymanager = (*env)->CallObjectMethod(env,mContext,jm_getSystemService,jo_telephonyService);
	jclass jc_telephonyManager = (*env)->FindClass(env,"android/telephony/TelephonyManager");
	//getLine1Number
	jmethodID jm_getLine1Number = (*env)->GetMethodID(env,jc_telephonyManager,"getLine1Number","()Ljava/lang/String;");
	jobject jo_getLine1Number = (*env)->CallObjectMethod(env,jo_telephonymanager,jm_getLine1Number);
	char* number = jstringTostring(env,jo_getLine1Number);
	LOGV("jo_getLine1Number:%s",number);
	return (jstring)jo_getLine1Number;
}
//0×5检测设备IDS是不是"000000000000000"
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkDeviceIDS(JNIEnv*env,jclassthiz,jobjectmContext){
	jclass jc_context = (*env)->FindClass(env,"android/content/Context");
	jmethodID jm_getSystemService = (*env)->GetMethodID(env,jc_context,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID jf_TELEPHONY_SERVICE = (*env)->GetStaticFieldID(env,jc_context,"TELEPHONY_SERVICE","Ljava/lang/String;");
	jobject jo_telephonyService = (*env)->GetStaticObjectField(env,jc_context,jf_TELEPHONY_SERVICE);
	jobject jo_telephonymanager = (*env)->CallObjectMethod(env,mContext,jm_getSystemService,jo_telephonyService);
	jclass jc_telephonyManager = (*env)->FindClass(env,"android/telephony/TelephonyManager");
	jmethodID jm_getDeviceId = (*env)->GetMethodID(env,jc_telephonyManager,"getDeviceId","()Ljava/lang/String;");
	jobject deviceid = (*env)->CallObjectMethod(env,jo_telephonymanager,jm_getDeviceId);
	char* cdeviceid = jstringTostring(env,deviceid);
	LOGV("deviceid:%s",cdeviceid);
	return (jstring)deviceid;
}
//0×6检测imsiid是不是"310260000000000"
JNIEXPORT jstringJNICALLJava_com_example_findemulator_MainActivity_checkImsiIDS(JNIEnv*env,jclassthiz,jobjectmContext){
	jclass jc_context = (*env)->FindClass(env,"android/content/Context");
	jmethodID jm_getSystemService = (*env)->GetMethodID(env,jc_context,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID jf_TELEPHONY_SERVICE = (*env)->GetStaticFieldID(env,jc_context,"TELEPHONY_SERVICE","Ljava/lang/String;");
	jobject jo_telephonyService = (*env)->GetStaticObjectField(env,jc_context,jf_TELEPHONY_SERVICE);
	jobject jo_telephonymanager = (*env)->CallObjectMethod(env,mContext,jm_getSystemService,jo_telephonyService);
	jclass jc_telephonyManager = (*env)->FindClass(env,"android/telephony/TelephonyManager");
	//getSubscriberId
	jmethodID jm_getSubscriberId = (*env)->GetMethodID(env,jc_telephonyManager,"getSubscriberId","()Ljava/lang/String;");
	jobject jo_SubscriberId = (*env)->CallObjectMethod(env,jo_telephonymanager,jm_getSubscriberId);
	char* cjo_SubscriberId = jstringTostring(env,jo_SubscriberId);
	LOGV("SubscriberId:%s",cjo_SubscriberId);
	return (jstring)jo_SubscriberId;
}
//0×7检测手机上的一些硬件信息
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkEmulatorBuild(JNIEnv*env,jclassthiz,jobjectmContext){
	jclass jc_build = (*env)->FindClass(env,"android/os/Build");
	//Board 
	jfieldID jf_BOARD = (*env)->GetStaticFieldID(env,jc_build,"BOARD","Ljava/lang/String;");
	jstring js_board = (*env)->GetStaticObjectField(env,jc_build,jf_BOARD);
	char* cjs_board = jstringTostring(env,js_board);
	LOGV("Board:%s",cjs_board);
	//BOOTLOADER 
	jfieldID jf_BOOTLOADER = (*env)->GetStaticFieldID(env,jc_build,"BOOTLOADER","Ljava/lang/String;");
	jstring js_bootloader = (*env)->GetStaticObjectField(env,jc_build,jf_BOOTLOADER);
	char* cjs_bootloader = jstringTostring(env,js_bootloader);
	LOGV("bootloader:%s",cjs_bootloader);
	//BRAND
	jfieldID jf_BRAND = (*env)->GetStaticFieldID(env,jc_build,"BRAND","Ljava/lang/String;");
	jstring js_brand = (*env)->GetStaticObjectField(env,jc_build,jf_BRAND);
	char* cjs_brand = jstringTostring(env,js_brand);
	LOGV("brand:%s",cjs_brand);
	//DEVICE
	jfieldID jf_DEVICE = (*env)->GetStaticFieldID(env,jc_build,"DEVICE","Ljava/lang/String;");
	jstring js_device = (*env)->GetStaticObjectField(env,jc_build,jf_DEVICE);
	char* cjs_device = jstringTostring(env,js_device);
	LOGV("device:%s",cjs_device);
	//HARDWARE
	jfieldID jf_HARDWARE = (*env)->GetStaticFieldID(env,jc_build,"HARDWARE","Ljava/lang/String;");
	jstring js_hardware = (*env)->GetStaticObjectField(env,jc_build,jf_HARDWARE);
	char* cjs_hardware = jstringTostring(env,js_hardware);
	LOGV("hardware:%s",cjs_hardware);
	//MODEL
	jfieldID jf_MODEL = (*env)->GetStaticFieldID(env,jc_build,"MODEL","Ljava/lang/String;");
	jstring js_model = (*env)->GetStaticObjectField(env,jc_build,jf_MODEL);
	char* cjs_model = jstringTostring(env,js_model);
	LOGV("model:%s",cjs_model);
	//PRODUCT
	jfieldID jf_PRODUCT = (*env)->GetStaticFieldID(env,jc_build,"PRODUCT","Ljava/lang/String;");
	jstring js_product = (*env)->GetStaticObjectField(env,jc_build,jf_PRODUCT);
	char* cjs_product = jstringTostring(env,js_product);
	LOGV("product:%s",cjs_product);
	if(js_board=="unknown"||js_bootloader=="unknown"||js_brand=="generic"||js_device=="generic"||js_model=="sdk"||js_product=="sdk"||js_hardware=="goldfish"){
		return (*env)->NewStringUTF(env,"FindEmulatorBycheckBuild!");
	} 
	else{
		return (*env)->NewStringUTF(env,"NotFindEmulatorBycheckBuild!");
	}
}
//0×8检测手机运营商家
JNIEXPORT jstring JNICALL Java_com_example_findemulator_MainActivity_checkOperatorNameAndroid(JNIEnv* env,jclass thiz,jobject mContext){
	jclass jc_context = (*env)->FindClass(env,"android/content/Context");
	jmethodID jm_getSystemService = (*env)->GetMethodID(env,jc_context,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
	jfieldID jf_TELEPHONY_SERVICE = (*env)->GetStaticFieldID(env,jc_context,"TELEPHONY_SERVICE","Ljava/lang/String;");
	jobject jo_telephonyService = (*env)->GetStaticObjectField(env,jc_context,jf_TELEPHONY_SERVICE);
	jobject jo_telephonymanager = (*env)->CallObjectMethod(env,mContext,jm_getSystemService,jo_telephonyService);
	jclass jc_telephonyManager = (*env)->FindClass(env,"android/telephony/TelephonyManager");
	//getNetworkOperatorName
	jmethodID jm_getNetworkOperatorName = (*env)->GetMethodID(env,jc_telephonyManager,"getNetworkOperatorName","()Ljava/lang/String;");
	jobject jo_NetworkOperatorName = (*env)->CallObjectMethod(env,jo_telephonymanager,jm_getNetworkOperatorName);
	char* cjo_NetworkOperatorName = jstringTostring(env,jo_NetworkOperatorName);
	LOGV("NetworkOperatorName:%s",cjo_NetworkOperatorName);
	return (jstring)jo_NetworkOperatorName;
}
