#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "igus_rebel_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__msg__DigitalOutput() -> *const std::ffi::c_void;
}

#[link(name = "igus_rebel_msgs__rosidl_generator_c")]
extern "C" {
    fn igus_rebel_msgs__msg__DigitalOutput__init(msg: *mut DigitalOutput) -> bool;
    fn igus_rebel_msgs__msg__DigitalOutput__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DigitalOutput>, size: usize) -> bool;
    fn igus_rebel_msgs__msg__DigitalOutput__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DigitalOutput>);
    fn igus_rebel_msgs__msg__DigitalOutput__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DigitalOutput>, out_seq: *mut rosidl_runtime_rs::Sequence<DigitalOutput>) -> bool;
}

// Corresponds to igus_rebel_msgs__msg__DigitalOutput
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DigitalOutput {

    // This member is not documented.
    #[allow(missing_docs)]
    pub output: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_on: bool,

}



impl Default for DigitalOutput {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !igus_rebel_msgs__msg__DigitalOutput__init(&mut msg as *mut _) {
        panic!("Call to igus_rebel_msgs__msg__DigitalOutput__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DigitalOutput {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__msg__DigitalOutput__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__msg__DigitalOutput__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { igus_rebel_msgs__msg__DigitalOutput__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DigitalOutput {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DigitalOutput where Self: Sized {
  const TYPE_NAME: &'static str = "igus_rebel_msgs/msg/DigitalOutput";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__igus_rebel_msgs__msg__DigitalOutput() }
  }
}


