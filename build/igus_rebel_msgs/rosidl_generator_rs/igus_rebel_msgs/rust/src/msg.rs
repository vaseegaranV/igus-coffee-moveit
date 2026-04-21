#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to igus_rebel_msgs__msg__DigitalOutput

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DigitalOutput::default())
  }
}

impl rosidl_runtime_rs::Message for DigitalOutput {
  type RmwMsg = super::msg::rmw::DigitalOutput;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        output: msg.output,
        is_on: msg.is_on,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      output: msg.output,
      is_on: msg.is_on,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      output: msg.output,
      is_on: msg.is_on,
    }
  }
}


