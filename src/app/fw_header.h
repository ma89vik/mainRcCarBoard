// Copyright 2020 Marius
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#define FW_TYPE_APP         1
#define FW_MAGIC_NUMBER     0xBEAD
#define FW_HEADER_VERSION   1

typedef struct __attribute__((packed)) {
    uint16_t fw_magic;
    uint16_t fw_hdr_version;
    uint32_t crc;
    uint32_t data_size;
    uint8_t fw_type;
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t version_patch;
    uint32_t vector_addr;
    uint32_t reserved;
    char git_sha[8];
    char fw_sha256[16];
} fw_hdr_t;