create trigger InsertCategoryWithParent -- name of the trigger
on CategoryWithParent -- name of the view
instead of insert    -- trigger code executed insted of insert
as
begin
  declare @newname nvarchar(255) -- variables used below
  declare @parentname nvarchar(255)

  -- using a cursor to navigate the inserted table
  declare ic cursor for select * from inserted
  open ic
  -- standard way of managing a cursor
  fetch next from ic into @newname, @parentname
  while @@FETCH_STATUS = 0
  begin
	if @parentname is null
	begin
		insert into Category (Name)
		values(@newname)
	end
	else
	begin
		declare @parentID int

		select @parentID = c.ID 
		from Category c 
		where c.Name = @parentname

		if @parentID is null
			throw 51000, 'Parent Category does not exist', 1;
		else
		begin
			insert into Category (Name, ParentCategoryID)
			values(@newname, @parentID)
		end
	end
    -- check the received values available in the variables
    -- find the id of the parent, if specified
    -- throw error if anything is not right
    -- or insert the record into the Category table
    fetch next from ic into @newname, @parentname
  end

  close ic -- finish cursor usage
  deallocate ic
end