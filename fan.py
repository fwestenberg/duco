import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import fan
from esphome.const import (
    CONF_ID,
    CONF_UPDATE_INTERVAL,
    CONF_SPEED,
    CONF_SPEED_COUNT
)
from esphome.core import CORE, coroutine

AUTO_LOAD = ["fan"]

# DucoVentilation = cg.global_ns.class_("DucoBox", fan.Fan, cg.PollingComponent)

duco_fan_ns = cg.esphome_ns.namespace("duco")
DucoFan = duco_fan_ns.class_("DucoFan", cg.Component)

# CONFIG_SCHEMA = fan.FAN_SCHEMA.extend(cv.COMPONENT_SCHEMA)
CONFIG_SCHEMA = fan.FAN_SCHEMA.extend(
    {
        # cv.GenerateID(CONF_ID): cv.declare_id(DucoFan),
#         cv.Optional(CONF_UPDATE_INTERVAL, default="10000ms"): cv.All(
#             cv.update_interval,
#             cv.Range(max=cv.TimePeriod(seconds=60))
#         )
    }
).extend(cv.COMPONENT_SCHEMA)


# async def register_duco(var, config):
async def to_code(config):
    # var = cg.new_Pvariable(config[CONF_ID])
    config[CONF_SPEED_COUNT] = 4
    config[CONF_SPEED] = 100

    state = await fan.create_fan_state(config)
    # await cg.register_component(var, config)


    # serial = HARDWARE_UART_TO_SERIAL[config[CONF_HARDWARE_UART]]
    # var = cg.new_Pvariable(config[CONF_ID])
    # await cg.register_component(var, config)

    # state = await fan.create_fan_state(config)
    # var = cg.new_Pvariable(config[CONF_ID])
    # await fan.register_fan(var, config)
    # await cg.register_component(var, config)

    # yield cg.register_component(var, config)
    # yield fan.register_fan(var, config)
    # cg.add_library("https://github.com/arnemauer/Ducobox-ESPEasy-Plugin", None)

