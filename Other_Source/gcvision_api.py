import requests
import base64
import json


GOOGLE_CLOUD_VISION_API_URL = 'https://vision.googleapis.com/v1/images:annotate?key='
API_KEY = 'AIzaSyCCVtGCmcb6ijyUAZQ8sVeK1b4EkHa0k2k'


def request_cloud_vison_api(image_base64):
    api_url = GOOGLE_CLOUD_VISION_API_URL + API_KEY
    req_body = json.dumps({
        'requests': [{
            'image': {
                
                'content': image_base64.decode('utf-8')
            },
            'features': [{
                
                'type': 'TEXT_DETECTION',
                'maxResults': 10,
            }]
        }]
    })
    res = requests.post(api_url, data=req_body)
    return res.json()
  
def img_to_base64(filepath):
  with open(filepath, 'rb') as img:
      img_byte = img.read()
  return base64.b64encode(img_byte)

def output_result(img_list):
  img_base64 = img_to_base64('./test.jpeg')
  result = request_cloud_vison_api(img_base64)
  text_r = result["responses"][0]["textAnnotations"][1]["description"]
  print(text_r);
  return text_r
