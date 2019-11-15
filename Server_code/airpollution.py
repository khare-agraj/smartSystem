import csv
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

# Fetch the service account key JSON file contents
cred = credentials.Certificate('firebase-adminsdk.json')
# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://data-transfer-e1ae6.firebaseio.com/'
})


with open("data.csv", 'r') as csvfile:
    reader = csv.reader(csvfile)
    for lat, lon, pol in reader:
        data = '{0:.6f}-{1:.6f}'.format(
            float(lat), float(lon)).replace('.', '\'')
        print(data)
        firebase_admin.db.reference(data).set(
            pol
        )


csvfile.close()
