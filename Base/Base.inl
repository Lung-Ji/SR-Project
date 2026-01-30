
Base::Base() : ReferenceCount(0) {	}
Base::~Base() {	}

unsigned long Base::AddRef() {
	return ++ReferenceCount;
}
unsigned long Base::Release() {

	if (ReferenceCount == 0) {
		Free();

		delete this;

		return 0;
	}

	return ReferenceCount--;
}

