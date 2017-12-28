#include "Ctu.h"

uint32_t nn::am::service::ICommonStateGetter::GetEventHandle(OUT shared_ptr<KObject>& _0) {
	shared_ptr<Waitable> waitobj = make_shared<Waitable>();
        waitobj->signal(0);
        _0 = waitobj;
	return 0;
}

uint32_t nn::am::service::ICommonStateGetter::ReceiveMessage(OUT nn::am::AppletMessage& _0) {
	_0 = 0xF;
	return 0;
}

uint32_t nn::am::service::ICommonStateGetter::GetCurrentFocusState(OUT uint8_t& _0) {
	_0 = 1;
	return 0;
}

uint32_t nn::am::service::IWindowController::GetAppletResourceUserId(OUT nn::applet::AppletResourceUserId& _0) {
	_0 = 1;
	return 0;
}

uint32_t nn::am::service::IStorageAccessor::GetSize(OUT int64_t& _0) {
	_0 = 0x88;//For sdk-nso "nn::account::detail::TryPopPreselectedUser()"
	return 0;
}

uint32_t nn::am::service::IStorageAccessor::Read(IN int64_t _0, OUT uint8_t * _1, guint _1_size) {
	memset(_1, 0, _1_size);
	if(_1_size != 0x88)return 0;//For sdk-nso "nn::account::detail::TryPopPreselectedUser()"

	uint32_t *buf = (uint32_t*)_1;

	buf[0] = 0xc79497ca;//magicnum(s)
	buf[1] = 1;

	buf[2] = 0x11223344;//userid
	buf[3] = 0x55667788;

	return 0;
}
