import xlrd

book = xlrd.open_workbook("connectome.xlsx")
chem_sheet = book.sheet_by_name("male chemical")
gap_sheet = book.sheet_by_name("male gap jn asymmetric")
out_file = open("male_connections.txt", 'w')

   # get row and column labels from tables
chem_col_labels = [str(cell).split("'")[1] for cell in chem_sheet.row(2)]
chem_row_labels = [str(cell).split("'")[1] for cell in chem_sheet.col(2)]
gap_col_labels = [str(cell).split("'")[1] for cell in gap_sheet.row(2)]
gap_row_labels = [str(cell).split("'")[1] for cell in gap_sheet.col(2)]

connections = []    # holds each connection in the format [presynaptic, postsynaptic, weight]

for j, postsynaptic in enumerate(chem_col_labels):
    for i, presynaptic in enumerate(chem_row_labels):
        if postsynaptic != "" and presynaptic != "" and chem_sheet.cell_value(i,j) != "":
            connections.append([presynaptic, postsynaptic, str(chem_sheet.cell_value(i,j))])

for j, col_neuron in enumerate(gap_col_labels):
    for i, row_neuron in enumerate(gap_row_labels):
        if col_neuron != "" and row_neuron != "" and gap_sheet.cell_value(i,j) != "":
            connections.append([col_neuron, row_neuron, str(gap_sheet.cell_value(i,j))])
            connections.append([row_neuron, col_neuron, str(gap_sheet.cell_value(i,j))])

for connection in connections:
    out_file.write(','.join(connection)+'\n')
