//
//  testAR.hpp
//  AugumentedReality
//
//  Created by Imama Noor on 8/25/16.
//  Copyright © 2016 Imama. All rights reserved.
//

#ifndef testAR_hpp
#define testAR_hpp


#endif /* testAR_hpp */

#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>

#include "AugmentedReality.h"

using namespace std;

class TestAR : public CppUnit::TestFixture {
private:
    AugmentedReality *testAugReal;
public:
    TestAR() { testAugReal = new AugmentedReality;}
    virtual ~TestAR() {
        delete testAugReal;
    }
    
    static CppUnit::Test *suite() {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("VideoProcess");
        
        suiteOfTests->addTest(new CppUnit::TestCaller<TestAR>("Test1 - VideoProcess.",
                                                                       &TestAR::testAugReal_Process ));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestAR>("Test1 - CamParamRead.",
                                                              &TestAR::testAugReal_Process ));
        
        return suiteOfTests;
    }
    
    /// Setup method
    void setUp() {
        testAugReal = new AugmentedReality;
    }
    
    /// Teardown method
    void tearDown() {
        delete testAugReal;
    }
    
protected:
    void testAugReal_Process() {
        int val = 0;
        int valClass = testAugReal->readFromFileCP("/Users/imamanoor/Documents/jobApplications/noor-vision-augmented-reality/AugumentedReality/AugumentedReality/intrinsics.yml");

        CPPUNIT_ASSERT( valClass == val );
    }
    void testAugReal_CamParamReader() {
        int val = 0;
        testAugReal->readFromFileCP("/Users/imamanoor/Documents/jobApplications/noor-vision-augmented-reality/AugumentedReality/AugumentedReality/intrinsics.yml");
        
        VideoCapture cap("/Users/imamanoor/Documents/jobApplications/noor-vision-augmented-reality/AugumentedReality/AugumentedReality/input1.m4v");
        int valClass = testAugReal->processVideo(cap);
        CPPUNIT_ASSERT( valClass == val );
    }
};
