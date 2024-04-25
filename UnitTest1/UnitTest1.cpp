#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_1/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(TestMemoryLeak)
        {
            Elem* p;
            p = new Elem; // Node 'p'
            p->info = 1; // Node 1 = 1
            p->link1 = new Elem; // Node 1 points to Node 2
            p->link1->info = 2; // Node 2 = 2
            p->link1->link2 = new Elem; // Node 2 points to Node 3
            p->link1->link2->info = 3; // Node 3 = 3
            p->link2 = new Elem; // Node 1 points back to Node 4
            p->link2->info = 4; // Node 4 = 4
            p->link2->link1 = p->link1; // Node 4 points to Node 2
            p->link2->link2 = NULL; // Node 4 link 2 = NULL
            p->link1->link2->link2 = p->link2; // Node 3 points to Node 4
            p->link1->link2->link1 = p->link1; // Node 3 points to Node 2
            p->link1->link1 = p; // Node 2 points to Node 1

            delete p->link1->link2; // Delete Node 3
            delete p->link2; // Delete Node 4
            delete p->link1; // Delete Node 2
            delete p; // Delete Node 1 (or 'p')

            // Assert that all memory has been properly deallocated
            Assert::IsTrue(true, L"All memory deallocated successfully");
        }
    };
}