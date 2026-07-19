if ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_CANCELABLE_TEXT app PRIVATE
    src/behaviors/behavior_cancelable_text.c
  )
endif()
