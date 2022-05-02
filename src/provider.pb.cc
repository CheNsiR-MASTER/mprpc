// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: provider.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "provider.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace mprpc {

namespace {

const ::google::protobuf::Descriptor* rpcHeader_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  rpcHeader_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_provider_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_provider_2eproto() {
  protobuf_AddDesc_provider_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "provider.proto");
  GOOGLE_CHECK(file != NULL);
  rpcHeader_descriptor_ = file->message_type(0);
  static const int rpcHeader_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(rpcHeader, service_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(rpcHeader, method_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(rpcHeader, args_size_),
  };
  rpcHeader_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      rpcHeader_descriptor_,
      rpcHeader::default_instance_,
      rpcHeader_offsets_,
      -1,
      -1,
      -1,
      sizeof(rpcHeader),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(rpcHeader, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(rpcHeader, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_provider_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      rpcHeader_descriptor_, &rpcHeader::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_provider_2eproto() {
  delete rpcHeader::default_instance_;
  delete rpcHeader_reflection_;
}

void protobuf_AddDesc_provider_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_provider_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016provider.proto\022\005mprpc\"I\n\trpcHeader\022\024\n\014"
    "service_name\030\001 \001(\014\022\023\n\013method_name\030\002 \001(\014\022"
    "\021\n\targs_size\030\003 \001(\005b\006proto3", 106);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "provider.proto", &protobuf_RegisterTypes);
  rpcHeader::default_instance_ = new rpcHeader();
  rpcHeader::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_provider_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_provider_2eproto {
  StaticDescriptorInitializer_provider_2eproto() {
    protobuf_AddDesc_provider_2eproto();
  }
} static_descriptor_initializer_provider_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int rpcHeader::kServiceNameFieldNumber;
const int rpcHeader::kMethodNameFieldNumber;
const int rpcHeader::kArgsSizeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

rpcHeader::rpcHeader()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:mprpc.rpcHeader)
}

void rpcHeader::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

rpcHeader::rpcHeader(const rpcHeader& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:mprpc.rpcHeader)
}

void rpcHeader::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  service_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  args_size_ = 0;
}

rpcHeader::~rpcHeader() {
  // @@protoc_insertion_point(destructor:mprpc.rpcHeader)
  SharedDtor();
}

void rpcHeader::SharedDtor() {
  service_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void rpcHeader::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* rpcHeader::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return rpcHeader_descriptor_;
}

const rpcHeader& rpcHeader::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_provider_2eproto();
  return *default_instance_;
}

rpcHeader* rpcHeader::default_instance_ = NULL;

rpcHeader* rpcHeader::New(::google::protobuf::Arena* arena) const {
  rpcHeader* n = new rpcHeader;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void rpcHeader::Clear() {
// @@protoc_insertion_point(message_clear_start:mprpc.rpcHeader)
  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  method_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  args_size_ = 0;
}

bool rpcHeader::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:mprpc.rpcHeader)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bytes service_name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_service_name()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_method_name;
        break;
      }

      // optional bytes method_name = 2;
      case 2: {
        if (tag == 18) {
         parse_method_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_method_name()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_args_size;
        break;
      }

      // optional int32 args_size = 3;
      case 3: {
        if (tag == 24) {
         parse_args_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &args_size_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:mprpc.rpcHeader)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:mprpc.rpcHeader)
  return false;
#undef DO_
}

void rpcHeader::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:mprpc.rpcHeader)
  // optional bytes service_name = 1;
  if (this->service_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      1, this->service_name(), output);
  }

  // optional bytes method_name = 2;
  if (this->method_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->method_name(), output);
  }

  // optional int32 args_size = 3;
  if (this->args_size() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->args_size(), output);
  }

  // @@protoc_insertion_point(serialize_end:mprpc.rpcHeader)
}

::google::protobuf::uint8* rpcHeader::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:mprpc.rpcHeader)
  // optional bytes service_name = 1;
  if (this->service_name().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->service_name(), target);
  }

  // optional bytes method_name = 2;
  if (this->method_name().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->method_name(), target);
  }

  // optional int32 args_size = 3;
  if (this->args_size() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->args_size(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:mprpc.rpcHeader)
  return target;
}

int rpcHeader::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:mprpc.rpcHeader)
  int total_size = 0;

  // optional bytes service_name = 1;
  if (this->service_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->service_name());
  }

  // optional bytes method_name = 2;
  if (this->method_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->method_name());
  }

  // optional int32 args_size = 3;
  if (this->args_size() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->args_size());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void rpcHeader::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mprpc.rpcHeader)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const rpcHeader* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const rpcHeader>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mprpc.rpcHeader)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mprpc.rpcHeader)
    MergeFrom(*source);
  }
}

void rpcHeader::MergeFrom(const rpcHeader& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mprpc.rpcHeader)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.service_name().size() > 0) {

    service_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  if (from.method_name().size() > 0) {

    method_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.method_name_);
  }
  if (from.args_size() != 0) {
    set_args_size(from.args_size());
  }
}

void rpcHeader::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mprpc.rpcHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void rpcHeader::CopyFrom(const rpcHeader& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mprpc.rpcHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool rpcHeader::IsInitialized() const {

  return true;
}

void rpcHeader::Swap(rpcHeader* other) {
  if (other == this) return;
  InternalSwap(other);
}
void rpcHeader::InternalSwap(rpcHeader* other) {
  service_name_.Swap(&other->service_name_);
  method_name_.Swap(&other->method_name_);
  std::swap(args_size_, other->args_size_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata rpcHeader::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = rpcHeader_descriptor_;
  metadata.reflection = rpcHeader_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// rpcHeader

// optional bytes service_name = 1;
void rpcHeader::clear_service_name() {
  service_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& rpcHeader::service_name() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcHeader.service_name)
  return service_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void rpcHeader::set_service_name(const ::std::string& value) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.rpcHeader.service_name)
}
 void rpcHeader::set_service_name(const char* value) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.rpcHeader.service_name)
}
 void rpcHeader::set_service_name(const void* value, size_t size) {
  
  service_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.rpcHeader.service_name)
}
 ::std::string* rpcHeader::mutable_service_name() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.rpcHeader.service_name)
  return service_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* rpcHeader::release_service_name() {
  // @@protoc_insertion_point(field_release:mprpc.rpcHeader.service_name)
  
  return service_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void rpcHeader::set_allocated_service_name(::std::string* service_name) {
  if (service_name != NULL) {
    
  } else {
    
  }
  service_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), service_name);
  // @@protoc_insertion_point(field_set_allocated:mprpc.rpcHeader.service_name)
}

// optional bytes method_name = 2;
void rpcHeader::clear_method_name() {
  method_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& rpcHeader::method_name() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcHeader.method_name)
  return method_name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void rpcHeader::set_method_name(const ::std::string& value) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mprpc.rpcHeader.method_name)
}
 void rpcHeader::set_method_name(const char* value) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mprpc.rpcHeader.method_name)
}
 void rpcHeader::set_method_name(const void* value, size_t size) {
  
  method_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mprpc.rpcHeader.method_name)
}
 ::std::string* rpcHeader::mutable_method_name() {
  
  // @@protoc_insertion_point(field_mutable:mprpc.rpcHeader.method_name)
  return method_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* rpcHeader::release_method_name() {
  // @@protoc_insertion_point(field_release:mprpc.rpcHeader.method_name)
  
  return method_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void rpcHeader::set_allocated_method_name(::std::string* method_name) {
  if (method_name != NULL) {
    
  } else {
    
  }
  method_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), method_name);
  // @@protoc_insertion_point(field_set_allocated:mprpc.rpcHeader.method_name)
}

// optional int32 args_size = 3;
void rpcHeader::clear_args_size() {
  args_size_ = 0;
}
 ::google::protobuf::int32 rpcHeader::args_size() const {
  // @@protoc_insertion_point(field_get:mprpc.rpcHeader.args_size)
  return args_size_;
}
 void rpcHeader::set_args_size(::google::protobuf::int32 value) {
  
  args_size_ = value;
  // @@protoc_insertion_point(field_set:mprpc.rpcHeader.args_size)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace mprpc

// @@protoc_insertion_point(global_scope)