from pyspark.sql import functions as F
from pyspark.sql import Window

# 1. Leer los archivos del disco
reproducciones = spark.read.parquet("reproducciones.parquet")
usuarios = spark.read.parquet("usuarios.parquet")

# 2. Filtrar solo a los usuarios Premium
usuarios_premium = usuarios.filter(usuarios["tipo_suscripcion"] == "Premium")

# 3. Cruzar las reproducciones con los datos de usuarios Premium
reproducciones_premium = reproducciones.join(usuarios_premium, "id_usuario")

# 4. Crear una ventana para contar cuántas canciones ha escuchado cada usuario en total
ventana_usuario = Window.partitionBy("id_usuario")
ranking_df = reproducciones_premium.withColumn("total_escuchado", F.count("id_cancion").over(ventana_usuario))

# 5. Filtrar para quedarnos solo con los usuarios ultra activos (más de 1,000 reproducciones)
usuarios_top = ranking_df.filter("total_escuchado > 1000")

# 6. Obtener el número final de usuarios únicos que cumplen esta condición
total_usuarios_top = usuarios_top.select("id_usuario").distinct().count()

# 7. Imprimir el resultado en la consola
print(f"Total de usuarios top Premium: {total_usuarios_top}")
