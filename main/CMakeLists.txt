idf_component_register(SRCS "main.c"
                       PRIV_REQUIRES spi_flash output_pin_toggler random_number_getter
                       INCLUDE_DIRS ".")
