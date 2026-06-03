from pyspark.sql import functions as F
from pyspark.sql import Window

# 1. Leer el archivo de ventas del disco duro
ventas = spark.read.parquet("ventas_historicas.parquet")

# 2. Filtrar para quedarnos solo con la categoría "Electrónica"
electronica = ventas.filter(ventas["categoria"] == "Electrónica")

# 3. Crear una columna con el monto con un impuesto del 21% agregado
electronica_con_impuesto = electronica.withColumn("monto_final", electronica["monto_total"] * 1.21)

# 4. Crear una ventana para obtener el monto máximo vendido por cada fecha diferente
ventana_fecha = Window.partitionBy("fecha")  ### SEGUNDO STAGE encontrado pero seguimso en el mismo JOB
ventas_con_maximo = electronica_con_impuesto.withColumn("max_venta_del_dia", F.max("monto_final").over(ventana_fecha))

# 5. Quedarnos solo con las ventas que igualaron ese monto máximo de su día
ventas_record = ventas_con_maximo.filter("monto_final == max_venta_del_dia")

# 6. ACCIÓN 1: Contar cuántas ventas récord de electrónica tuvimos en la historia
total_records = ventas_record.count()

# 7. ACCIÓN 2: Mostrar en pantalla las primeras 5 ventas récord
ventas_record.select("id_transaccion", "fecha", "monto_final").show(5)

# 8. Imprimir el conteo final
print(f"Total de ventas récord: {total_records}")
