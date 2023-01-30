import paho.mqtt.client as paho

# MQTT client to the ThingsBoard device, that publish telemetries to be shown on the web onterface


class MQTT_client:
    # at init create paho client and connect to the broker
    def __init__(self, ACCESS_TOKEN='67v7kSViFKVYDccBawvd', broker="demo.thingsboard.io", port=1883):
        self.client = paho.Client(client_id="control1")  # create client object
        self.client.on_publish = self.on_publish  # assign function to callback
        # access token from thingsboard device
        self.client.username_pw_set(ACCESS_TOKEN)
        self.client.connect(broker, port, keepalive=60)  # establish connection
        print("connected to the broker")

    def on_publish(client, userdata, result):
        print("data published to thingsboard \n")

    # publish the data on topic "v1/devices/me/telemetry"
    def publish(self, payload):
        print("payload:")
        print(payload)
        # topic-v1/devices/me/telemetry
        ret = self.client.publish("v1/devices/me/telemetry", payload)
        print("Please check LATEST TELEMETRY field of your device")

    # disconnect the client
    def disconnect(self):
        self.client.disconnect()
        print("disconnected from MQTT broker")
