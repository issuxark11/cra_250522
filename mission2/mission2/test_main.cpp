#include "gmock/gmock.h"

#ifdef _DEBUG
int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#endif