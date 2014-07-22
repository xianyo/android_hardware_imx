/*
 * Copyright (C) 201e-2014 Embest Tech, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _OV2656CSI_H_
#define _OV2656CSI_H_

#include "OvDevice.h"

class Ov2656Csi : public OvDevice {
public:
    virtual status_t initSensorInfo(const CameraInfo& info);
	virtual int getCaptureMode(int width, int height);
};

#endif // ifndef _OV2656CSI_H_
