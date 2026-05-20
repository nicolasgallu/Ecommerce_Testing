import kagglehub
import openpyxl
#"""
#Download latest version
path = kagglehub.dataset_download("hammadansari7/e-commerce-orders-and-customer-analytics-dataset",
                                  output_dir='/home/nicolas/Escritorio/work/personal/snowflake_project/dataset',force_download=True)
print("Path to dataset files:", path)
#Understand the Data Structure
#"""

"""
# Check for missing values in the DataFrame
missing_values = data.isnull().sum()
print("Missing Values:")
print(missing_values)

# Check for duplicate rows in the DataFrame
duplicate_rows = data[data.duplicated()]
print("Duplicate Rows:")
print(duplicate_rows)

# Check data types of each column in the DataFrame
data_types = data.dtypes
print("Data Types:")
print(data_types)
"""



import pandas as pd
import csv
from datetime import datetime
data = pd.read_excel('dataset/ecommerce_orders_dataset.csv.xlsx')
data.to_csv('commerce_orders_dataset.csv',index=False)


print("starting eccomer dataset csv cleaning")
input_file = "commerce_orders_dataset.csv"
output_file = "commerce_orders_dataset_new.csv"

with open(input_file, "r", encoding="utf-8") as infile, \
     open(output_file, "w", encoding="utf-8", newline="") as outfile:
    
    # We read it as raw lines first if the commas are completely breaking the CSV structure
    reader = csv.reader(infile)
    writer = csv.writer(outfile)
    
    # Copy header
    header = next(reader)
    header.append('updated_at')
    writer.writerow(header)
    
    header = header[:-1]
    print(header)
    for row in reader:
        print(row)
        # Example: If your row normally has 5 columns, but rows with the bad float have 6
        if len(row) > len(header):
            print("yes")
            # Let's say the float was split across index 3 and 4 (e.g., ['id', 'name', '50.00', '00', 'status'])
            # Identify where the split happened based on your specific data structure:
            split_idx = 2 # Change this to the index where the number starts
            
            # Recombine the two broken pieces into a clean float string: "50000.00"
            thousands_part = row[split_idx].replace(".", "") # Remove the dots ("50.00" -> "5000")
            decimal_part = row[split_idx + 1]               # "00"
            clean_float = f"{thousands_part}.{decimal_part}" # "5000.00"
            
            # Reconstruct the row
            row[split_idx] = clean_float
            del row[split_idx + 1]
        row.append(datetime.now())
            
        writer.writerow(row)

print("CSV cleaned successfully!")


