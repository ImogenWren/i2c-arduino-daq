<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="21008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="controls" Type="Folder">
			<Item Name="all-sensor-data.ctl" Type="VI" URL="../all-sensor-data.ctl"/>
			<Item Name="SCD41.ctl" Type="VI" URL="../SCD41.ctl"/>
			<Item Name="SHT41.ctl" Type="VI" URL="../SHT41.ctl"/>
			<Item Name="STC31.ctl" Type="VI" URL="../STC31.ctl"/>
		</Item>
		<Item Name="depreciated" Type="Folder">
			<Item Name="integrated-serial-read.vi" Type="VI" URL="../integrated-serial-read.vi"/>
		</Item>
		<Item Name="sub-vi" Type="Folder">
			<Item Name="SCD41-string-array-to-data.vi" Type="VI" URL="../SCD41-string-array-to-data.vi"/>
			<Item Name="serial-csv-to-string-array.vi" Type="VI" URL="../serial-csv-to-string-array.vi"/>
			<Item Name="SHT41-string-array-to-data.vi" Type="VI" URL="../SHT41-string-array-to-data.vi"/>
			<Item Name="STC31-string-array-to-data.vi" Type="VI" URL="../STC31-string-array-to-data.vi"/>
		</Item>
		<Item Name="serial-read-subVi.vi" Type="VI" URL="../serial-read-subVi.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Delimited String to 1D String Array.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Delimited String to 1D String Array.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
