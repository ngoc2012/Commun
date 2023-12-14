from django.db import models

# Create your models here.
class SharedModel(models.Model):
    name = models.CharField(max_length=255)
    #description = models.TextField()
    id = models.CharField(max_length=255)

    def __str__(self):
        return self.name
