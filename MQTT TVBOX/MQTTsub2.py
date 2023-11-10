import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Conectado com código de resultado: " + str(rc))
    client.subscribe("TEMPERATURA")

def on_message(client, userdata, msg):
    print("Tópico: " + msg.topic + " - Mensagem: " + str(msg.payload))


client = mqtt.Client()

client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883) 

client.loop_forever()
