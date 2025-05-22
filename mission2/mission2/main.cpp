#include "gmock/gmock.h"
#include "fix_keyword.h"

#ifdef _DEBUG
int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
#else
int main() {
	fixKeyword objFixKeyword;
	objFixKeyword.fileInput();
}
#endif