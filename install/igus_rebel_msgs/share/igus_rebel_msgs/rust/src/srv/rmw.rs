#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "igus_rebel_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput_Request() -> *const std::ffi::c_void;
}

#[link(name = "igus_rebel_msgs__rosidl_generator_c")]
extern "C" {
    fn igus_rebel_msgs__srv__SetDigitalOutput_Request__init(msg: *mut SetDigitalOutput_Request) -> bool;
    fn igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Request>, size: usize) -> bool;
    fn igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Request>);
    fn igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetDigitalOutput_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Request>) -> bool;
}

// Corresponds to igus_rebel_msgs__srv__SetDigitalOutput_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetDigitalOutput_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub output: super::super::msg::rmw::DigitalOutput,

}



impl Default for SetDigitalOutput_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !igus_rebel_msgs__srv__SetDigitalOutput_Request__init(&mut msg as *mut _) {
        panic!("Call to igus_rebel_msgs__srv__SetDigitalOutput_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetDigitalOutput_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetDigitalOutput_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetDigitalOutput_Request where Self: Sized {
  const TYPE_NAME: &'static str = "igus_rebel_msgs/srv/SetDigitalOutput_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput_Request() }
  }
}


#[link(name = "igus_rebel_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput_Response() -> *const std::ffi::c_void;
}

#[link(name = "igus_rebel_msgs__rosidl_generator_c")]
extern "C" {
    fn igus_rebel_msgs__srv__SetDigitalOutput_Response__init(msg: *mut SetDigitalOutput_Response) -> bool;
    fn igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Response>, size: usize) -> bool;
    fn igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Response>);
    fn igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetDigitalOutput_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetDigitalOutput_Response>) -> bool;
}

// Corresponds to igus_rebel_msgs__srv__SetDigitalOutput_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetDigitalOutput_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetDigitalOutput_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !igus_rebel_msgs__srv__SetDigitalOutput_Response__init(&mut msg as *mut _) {
        panic!("Call to igus_rebel_msgs__srv__SetDigitalOutput_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetDigitalOutput_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__srv__SetDigitalOutput_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetDigitalOutput_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetDigitalOutput_Response where Self: Sized {
  const TYPE_NAME: &'static str = "igus_rebel_msgs/srv/SetDigitalOutput_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput_Response() }
  }
}






#[link(name = "igus_rebel_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput() -> *const std::ffi::c_void;
}

// Corresponds to igus_rebel_msgs__srv__SetDigitalOutput
#[allow(missing_docs, non_camel_case_types)]
pub struct SetDigitalOutput;

impl rosidl_runtime_rs::Service for SetDigitalOutput {
    type Request = SetDigitalOutput_Request;
    type Response = SetDigitalOutput_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__igus_rebel_msgs__srv__SetDigitalOutput() }
    }
}


