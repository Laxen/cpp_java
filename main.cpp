#include <jni.h>

#include <cassert>
#include <iostream>

#include <stdexcept>

jmethodID get_static_mid(JNIEnv* env, jclass class_j, std::string method_name, std::string signature);
jclass get_class(JNIEnv* env, std::string class_name);

int main(int argc, char** argv) {
	const int kNumOptions = 1;
	JavaVMOption options[kNumOptions] = {
		{ const_cast<char*>("-Djava.class.path=./my-app.jar"), NULL }
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

	jclass main_class = get_class(env, "rdf4j_get_statements_from_server");
	jmethodID main_mid = get_static_mid(env, main_class, "main", "([Ljava/lang/String;)V");
	env->CallStaticVoidMethod(main_class, main_mid, NULL);
	
	/*
	jclass main_class = get_class(env, "Main");
	jmethodID main_mid = get_static_mid(env, main_class, "main", "([Ljava/lang/String;)V");

	// Build argument array
	const jsize kNumArgs = 2;
	jclass string_class = env->FindClass("java/lang/String");
	jobject initial_element = NULL;
	jobjectArray method_args = env->NewObjectArray(kNumArgs, string_class, initial_element);
	jstring method_args_0 = env->NewStringUTF("Hello1, Java!");
	jstring method_args_1 = env->NewStringUTF("Hello2, Java!");
	env->SetObjectArrayElement(method_args, 0, method_args_0);
	env->SetObjectArrayElement(method_args, 1, method_args_1);

	// Call main() with above argument array
	env->CallStaticVoidMethod(main_class, main_mid, method_args);

	jmethodID invert_mid = get_static_mid(env, main_class, "invert", "(Z)Z");
	jboolean b = true;
	b = env->CallStaticBooleanMethod(main_class, invert_mid, b);
	std::string val = b ? "TRUE" : "False";
	std::cout << val << std::endl;
	*/

	jvm->DestroyJavaVM();
	return 0;
}

jclass get_class(JNIEnv* env, std::string class_name) {
	jclass c = env->FindClass(class_name.c_str());
	if (c == NULL) {
		throw std::runtime_error("get_class : Class \"" + class_name + "\" not found!");
	}
}

jmethodID get_static_mid(JNIEnv* env, jclass class_j, std::string method_name, std::string signature) {
	jmethodID mid = env->GetStaticMethodID(class_j, method_name.c_str(), signature.c_str());
	if (mid == NULL) {
		throw std::runtime_error("get_static_mid : Method \"" + method_name + "\" not found!");
	}
}
