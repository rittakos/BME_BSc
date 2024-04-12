create or alter trigger InvoiceItemCountMaintenance
on InvoiceItem
  after insert, delete, update
as

update Invoice
set ItemCount = isnull(ItemCount, 0) + Diff
from Invoice inner join 
		(select i.InvoiceID, sum(Amount) as Diff
		from inserted i
		group by i.InvoiceID)InvoiceChange
	on Invoice.ID = InvoiceChange.InvoiceID

update Invoice
set ItemCount = isnull(ItemCount, 0) - Diff
from Invoice inner join 
		(select d.InvoiceID, sum(Amount) as Diff
		from deleted d
		group by d.InvoiceID)InvoiceChange
	on Invoice.ID = InvoiceChange.InvoiceID