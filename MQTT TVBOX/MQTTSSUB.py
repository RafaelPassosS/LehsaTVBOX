import paho.mqtt.client as mqtt
import time

def on_message(client, userdata, message):
    print("Recebido:", str(message.payload.decode("utf-8")))

mqttBroker = "localhost"
client = mqtt.Client("Celular")
client.connect(mqttBroker,1883)

client.loop_start()

client.subscribe("TEMPERATURA")
client.on_message = on_message

time.sleep(30)
client.loop_stop()