#include "Ctu.h"

static bool vsync_initialized = 0;
static shared_ptr<Waitable> vsync_waitobj;

uint32_t nn::visrv::sf::IApplicationDisplayService::OpenLayer(IN nn::vi::DisplayName _0, IN uint64_t _1, IN nn::applet::AppletResourceUserId _2, IN gpid _3, OUT int64_t& _4, OUT uint8_t * _5, guint _5_size) {
	uint32_t *ptr = (uint32_t*)_5;
	_4 = 0;

	if(0x10+0x28 > _5_size) return -1;

	//ParcelDataSize
	*ptr++ = 0x28;
	_4+= 4;
	//ParcelDataOffset
	*ptr++ = 0x10;
	_4+= 4;
	//ParcelObjectsSize
	*ptr++ = 0x4;
	_4+= 4;
	//ParcelObjectsOffset
	*ptr++ = 0x10+0x28;
	_4+= 4;

	//ParcelData

	*ptr++ = 0x2;
	_4+= 4;

	//"Probably the user-process PID?"
	*ptr++ = 0x1;
	_4+= 4;

	//ID
	*ptr++ = 0x19;
	_4+= 4;

	*ptr++ = 0x0;
	_4+= 4;
	*ptr++ = 0x0;
	_4+= 4;
	*ptr++ = 0x0;
	_4+= 4;

	strncpy((char*)ptr, "dispdrv", 8);
	ptr+= 0x8>>2;
	_4+= 8;

	*ptr++ = 0x0;
	_4+= 4;
	*ptr++ = 0x0;
	_4+= 4;

	//ParcelObjects

	*ptr++ = 0x0;
	_4+= 4;

	return 0;
}

uint32_t nn::visrv::sf::IApplicationDisplayService::GetDisplayVsyncEvent(IN uint64_t _0, OUT shared_ptr<KObject>& _1) {
	vsync_waitobj = make_shared<Waitable>();
	vsync_initialized = 1;
	_1 = vsync_waitobj;
	return 0;
}

uint32_t nns::hosbinder::IHOSBinderDriver::GetNativeHandle(IN int32_t _0, IN uint32_t _1, OUT shared_ptr<KObject>& _2) {
	_2 = make_shared<Waitable>();
	return 0;
}

static uint32_t _TransactParcel(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size) {
	memset(_4, 0, _4_size);

	uint32_t *ptr = (uint32_t*)_4;

	if(_1==0x3) {
		if(vsync_initialized)vsync_waitobj->signal(0);
	}
	else if(_1==0x7) {
		if(0x10+0xc+0x8+0x24 > _4_size) return -1;

		//ParcelDataSize
		*ptr++ = 0xc+0x8+0x24;
		//ParcelDataOffset
		*ptr++ = 0x10;
		//ParcelObjectsSize
		*ptr++ = 0x0;
		//ParcelObjectsOffset
		*ptr++ = 0x10+0xc+0x8+0x24;

		//ParcelData

		//buf
		*ptr++ = 0;

		//fence flag
		*ptr++ = 1;

		//FlattenedObject

		//len
		*ptr++ = 0x24;

		//fd_count
		*ptr++ = 0;

		ptr+= 0x24>>2;

		//result
		*ptr++ = 0;
	}
	else if(_1==0xa) {
		if(0x10+0x10+0x4 > _4_size) return -1;

		//ParcelDataSize
		*ptr++ = 0x10+0x4;
		//ParcelDataOffset
		*ptr++ = 0x10;
		//ParcelObjectsSize
		*ptr++ = 0x0;
		//ParcelObjectsOffset
		*ptr++ = 0x10+0x10+0x4;

		//ParcelData

		//bufferProducerQueueBufferOutput

		//width
		*ptr++ = 1280;

		//height
		*ptr++ = 720;

		//transformHint
		*ptr++ = 0;

		//numPendingBuffers
		*ptr++ = 0;

		//result
		*ptr++ = 0;
	}

	return 0;
}

uint32_t nns::hosbinder::IHOSBinderDriver::TransactParcel(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size) {
	return _TransactParcel(_0, _1, _2, _3, _3_size, _4, _4_size);
}

uint32_t nns::hosbinder::IHOSBinderDriver::TransactParcelAuto(IN int32_t _0, IN uint32_t _1, IN uint32_t _2, IN uint8_t * _3, guint _3_size, OUT uint8_t * _4, guint _4_size) {
	return _TransactParcel(_0, _1, _2, _3, _3_size, _4, _4_size);
}
