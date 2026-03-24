from PIL import Image
import base64
import os
import google.generativeai as genai

# Configure the API key using the environment variable
genai.configure(api_key=os.environ["GEMINI_API_KEY"])

def describe_image(image_path):
    print(f"\n--- Analyzing {image_path} ---")
    try:
        # Load the image
        img = Image.open(image_path)
        
        # Initialize the model (using gemini-2.5-pro for best vision results)
        model = genai.GenerativeModel('gemini-2.5-pro')
        
        # Generate the description
        prompt = "Transcrire tout le texte visible dans cette image. Et decris brievement ce qui est demande."
        response = model.generate_content([prompt, img])
        
        print(response.text)
    except Exception as e:
        print(f"Error analyzing {image_path}: {e}")

images = [
    "kaba_balde/docs/photo_2026-03-24_14-26-52 (2).jpg",
    "kaba_balde/docs/photo_2026-03-24_14-26-52 (3).jpg",
    "kaba_balde/docs/photo_2026-03-24_14-26-52.jpg",
    "kaba_balde/docs/photo_2026-03-24_14-26-53 (2).jpg",
    "kaba_balde/docs/photo_2026-03-24_14-26-53.jpg"
]

for img_path in images:
    describe_image(img_path)
