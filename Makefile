CXXFLAGS =	-std=c++11 -O2 -g -Wall -fmessage-length=0 -I/usr/local/include

OBJS =		AugmentedReality.o

LIBS =		—lcppunit -lopencv_calib3d —lopencv_imgcodecs —lopencv_videoio —lopencv_videostab -lopencv_core -lopencv_highgui  -lopencv_imgproc -lopencv_video -lopencv_features2d  -lboost_system -lboost_filesystem -L/usr/local/lib -L/usr/lib

TARGET =	augmented-reality

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
