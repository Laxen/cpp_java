#include <jni.h>

#include <cassert>
#include <iostream>

int main(int argc, char** argv) {
	const char* java_class_name = "Main";
	const char* java_method_name = "main";

	const int kNumOptions = 1;
	JavaVMOption options[kNumOptions] = {
		{ const_cast<char*>("-Djava.class.path=./"), NULL }
	};

	JavaVMInitArgs vm_args;
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = kNumOptions;
	vm_args.options = options;

	JNIEnv* env;
	JavaVM* jvm;
	int res = JNI_CreateJavaVM(&jvm, reinterpret_cast<void**>(&env), &vm_args);
	if (res != JNI_OK) {
		std::cerr << "FAILED: JNI_CreateJavaVM " << res << std::endl;
		return -1;
	}

	jclass main_class = env->FindClass(java_class_name);
	if (main_class == NULL) {
		std::cerr << "FAILED: FindClass" << std::endl;
		return -1;
	}

	jmethodID main_method = env->GetStaticMethodID(main_class, java_method_name, "([Ljava/lang/String;)V");
	if (main_method == NULL) {
		std::cerr << "FAILED: GetStaticMethodID" << std::endl;
		return -1;
	}

	const jsize kNumArgs = 1;
	jclass string_class = env->FindClass("java/lang/String");
	jobject initial_element = NULL;
	jobjectArray method_args = env->NewObjectArray(kNumArgs, string_class, initial_element);

	jstring method_args_0 = env->NewStringUTF("Hello, Java!");
	env->SetObjectArrayElement(method_args, 0, method_args_0);

	env->CallStaticVoidMethod(main_class, main_method, method_args);
	jvm->DestroyJavaVM();

	return 0;
}
