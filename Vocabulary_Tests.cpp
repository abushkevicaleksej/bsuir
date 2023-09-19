#include "pch.h"
#include "CppUnitTest.h"
#include "../vocabularylib/vocclasses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vocabulary_Tests
{
	TEST_CLASS(Vocabulary_Tests)
	{
	public:
		
		TEST_METHOD(Test_Other_Way)
		{
			Vocabulary voc;
			Assert::IsTrue(voc.root == nullptr);
		}

		TEST_METHOD(Root_Emptying)
		{
			Vocabulary voc;
			string eng = "hen", rus = "kuritsa";
			voc.push(eng,rus, voc.InSubTree(eng));
			voc.empty();
			Assert::IsTrue(voc.root == NULL);
		}

		TEST_METHOD(Pushing_Using_Vocabulary)
		{
			Vocabulary voc;
			voc.push("cat", "kot", voc.InSubTree("cat"));
			voc.push("dog", "sobaka", voc.InSubTree("dog"));
			voc.push("cow", "korova", voc.InSubTree("cow"));
			voc.push("bird", "ptica", voc.InSubTree("bird"));
			voc.del("bird", "ptica");
			Assert::IsTrue(voc.size() == 3);
		}

		TEST_METHOD(Switcing_Using_Vocabulary)
		{
			Vocabulary voc;
			voc.push("cat", "kot", voc.InSubTree("cat"));
			voc.push("dog", "sobaka", voc.InSubTree("dog"));
			voc.push("cow", "korova", voc.InSubTree("cow"));
			voc.push("bird", "ptica", voc.InSubTree("bird"));
			voc.switch_transl("bird", "vorobei");
			Assert::IsTrue(voc["bird"]=="vorobei");
		}

		TEST_METHOD(Test_Get_Size)
		{
			Vocabulary voc;
			voc.push("cat", "kot", voc.InSubTree("cat"));
			voc.push("dog", "sobaka", voc.InSubTree("dog"));
			voc.push("cow", "korova", voc.InSubTree("cow"));
			voc.push("bird", "ptica", voc.InSubTree("bird"));
			Assert::IsTrue(voc["cat"] == "kot");
		}

		TEST_METHOD(IsEmpty)
		{
			Vocabulary voc;
			voc.push("cow", "korova", voc.InSubTree("cow"));
			voc.push("debugger", "otladchik",voc.InSubTree("debugger"));
			voc.push("eng", "angl", voc.InSubTree("eng"));
			voc.push("university", "universitet", voc.InSubTree("university"));
			voc.push("book", "kNiGA", voc.InSubTree("book"));
			Assert::IsTrue(voc.size() == 5);
		}

		TEST_METHOD(Test_Del)
		{
			Vocabulary voc;
			voc.push("cow", "korova", voc.InSubTree("cow"));
			voc.push("chair", "stul", voc.InSubTree("chair"));
			voc.del("chair", "stul");
			Assert::IsTrue(voc.size() == 1);
		}

		TEST_METHOD(Negative_Test_Change_Translation)
		{
			Vocabulary voc;
			voc.push("bird", "ptica", voc.InSubTree("bird"));
			voc.push("fox", "lisa", voc.InSubTree("fox"));
			voc.switch_transl("bird", "vorobei");
			voc.switch_transl("fox", "rijaya");
			Assert::IsTrue(voc.size() == 2);
		}

		TEST_METHOD(Negative_Test_Pull_File)
		{
			Vocabulary voc;
			voc.read_from_file("vocabulary.txt");
			Assert::IsTrue(voc.size() == 3);
		}

		TEST_METHOD(Translation)
		{
			Vocabulary voc;
			voc.push("oop","ооп", voc.InSubTree("oop"));
			voc.push("programming", "programmirovanie", voc.InSubTree("programming"));
			voc.switch_transl("programming","c++");
			voc.del("programming", (voc)["programming"]);
			Assert::IsTrue(voc.size() == 1);
		}
	};
}

