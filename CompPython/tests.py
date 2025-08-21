import requests

# Create a session
session = requests.Session()

# Set headers to be sent in every request
session.headers.update({'Accepts': 'application/json'})

# Perform multiple requests within the same session
response1 = session.get('https://example.com/some-page')
response2 = session.get('https://example.com/some-other-page')

print(response1)